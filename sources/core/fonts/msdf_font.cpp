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

	auto msdf_font::bind_and_clone(GlyphGeometry &glyph) const -> GlyphGeometry
	{
		glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, _conf.max_corner_angle, 0);
		glyph.wrapBox(_conf.glyph_scale, _conf.pixel_range/_conf.glyph_scale, _conf.miter_limit);

		return glyph;
	}

	auto msdf_font::atlas() -> msdf_dynamic_atlas&
	{
		return this->_atlas;
	}

	auto msdf_font::make(std::string font_path) -> std::shared_ptr<msdf_font>
	{
		return std::make_shared<msdf_font>(std::move(font_path));
	}
}