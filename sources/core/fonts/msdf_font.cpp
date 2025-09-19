//
// Created by ricka on 24/08/25.
//

#include <iostream>
#include <sdlk/core/fonts/msdf_font.hpp>
#include <stdexcept>

#include "free_type_handle_wrapper.hpp"

namespace sdlk
{
	msdf_font::msdf_font(std::string font_path, msdf_font_conf &&conf):
		_conf(conf),
		_font_path(std::move(font_path))
	{
		this->_font_handle = msdfgen::loadFont(free_type_handle_wrapper::instance()->raw(), _font_path.c_str());

		if (!this->_font_handle)
		{
			throw std::runtime_error("Could not load font " + _font_path);
		}

		std::vector<GlyphGeometry> glyphs{};
		FontGeometry fontGeometry(&glyphs);
		fontGeometry.loadCharset(this->_font_handle, 1.0, Charset::ASCII);

		for (auto &glyph: glyphs)
		{
			auto new_glyph = this->bind_and_clone(glyph);
			this->_glyphs_map.insert(std::make_pair(static_cast<char>(glyph.getCodepoint()), new_glyph));
		}

		this->_atlas.add(glyphs.data(), static_cast<int>(glyphs.size()));
		msdfgen::BitmapConstRef<byte, 3> bitmap{this->_atlas.atlasGenerator().atlasStorage()};

		glGenTextures(1, &this->_texture);
		glBindTexture(GL_TEXTURE_2D, this->_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width, bitmap.height, 0, GL_RGB, GL_UNSIGNED_BYTE, bitmap.pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	auto msdf_font::update_texture() -> void
	{
		const msdfgen::BitmapConstRef<byte, 3> bitmap{this->_atlas.atlasGenerator().atlasStorage()};
		glBindTexture(GL_TEXTURE_2D, this->_texture);
		glTexSubImage2D(GL_TEXTURE_2D, 0,0, 0, bitmap.width, bitmap.height,GL_RGB, GL_UNSIGNED_BYTE, bitmap.pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	 msdf_font::~msdf_font()
	{
		msdfgen::destroyFont(_font_handle);
		std::cout << "destroyed" << "\n";
	}

	auto msdf_font::get(char c) -> const GlyphGeometry&
	{
		auto it = this->_glyphs_map.find(c);
		if (it != this->_glyphs_map.end())
		{
			return it->second;
		}

		return this->load(c);
	}


	auto msdf_font::load(char c) -> const GlyphGeometry&
	{
		Charset charset;
		charset.add(c);

		std::vector<GlyphGeometry> glyphs{};
		FontGeometry fontGeometry(&glyphs);
		fontGeometry.loadGlyphset(this->_font_handle, 1.0, charset);

		auto new_glyph = this->bind_and_clone(glyphs.back());
		this->_glyphs_map.insert(std::make_pair(static_cast<char>(new_glyph.getCodepoint()), new_glyph));
		this->_atlas.add(glyphs.data(), static_cast<int>(glyphs.size()));

		return this->_glyphs_map[c];
	}

	auto msdf_font::texture() const -> const GLuint&
	{
		return this->_texture;
	}

	auto msdf_font::bind_and_clone(GlyphGeometry &glyph) const -> GlyphGeometry
	{
		glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, _conf.max_corner_angle, 0);
		glyph.wrapBox(_conf.glyph_scale, _conf.pixel_range/_conf.glyph_scale, _conf.miter_limit);

		return glyph;
	}

	auto msdf_font::atlas() -> msdf_dynamic_atlas&
	{
		msdfgen::Bitmap<byte, 3> bitmap{ this->_atlas.atlasGenerator().atlasStorage() };
		return this->_atlas;
	}

	auto msdf_font::make(std::string font_path) -> std::shared_ptr<msdf_font>
	{
		return std::make_shared<msdf_font>(std::move(font_path));
	}
}