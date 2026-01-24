//
// Created by ricka on 2026-01-18.
//

#include <sdlk/core/fonts/msdf_font.hpp>
#include <stdexcept>

#include "free_type_handle_wrapper.hpp"

namespace sdlk
{
	msdf_font::msdf_font(std::string font_path, msdf_font_conf &&conf)
		: m_conf(conf),
		  m_font_path(std::move(font_path))
	{
		this->m_font_handle =
			msdfgen::loadFont(free_type_handle_wrapper::instance()->raw(), m_font_path.c_str());

		if (!this->m_font_handle)
		{
			throw std::runtime_error("Could not load font " + m_font_path);
		}

		this->m_texture = std::make_shared<sdlk2d::texture>();
		glGenTextures(1, &this->m_texture->get_id());

		this->m_texture->bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		this->load(Charset::ASCII);
	}

	auto msdf_font::load(const char &character) -> void
	{
		Charset charset{};
		charset.add(character);
		return this->load(charset);
	}

	auto msdf_font::load(const Charset &charset) -> void
	{
		std::vector<GlyphGeometry> charset_glyphs;
		charset_glyphs.reserve(charset.size());

		FontGeometry font_geometry(&charset_glyphs);
		font_geometry.loadCharset(this->m_font_handle, 1.0, charset);

		for (auto &glyph : charset_glyphs)
		{
			auto new_glyph = this->configure(glyph);
			this->m_glyphs.insert(
				std::make_pair(static_cast<char>(glyph.getCodepoint()), new_glyph));
		}
		this->add_to_atlas(charset_glyphs);
	}

	auto msdf_font::get(const char &c) -> const GlyphGeometry &
	{
		const auto &it = this->m_glyphs.find(c);
		if (it != this->m_glyphs.end())
		{
			return it->second;
		}

		this->load(c);
		return this->get(c);
	}

	auto msdf_font::configure(GlyphGeometry &glyph) const -> GlyphGeometry
	{
		glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, m_conf.m_max_corner_angle, 0);
		glyph.wrapBox(m_conf.m_glyph_scale,
			m_conf.m_pixel_range / m_conf.m_glyph_scale,
			m_conf.m_miter_limit);

		return glyph;
	}

	auto msdf_font::add_to_atlas(std::vector<GlyphGeometry> glyphs)
		-> msdf_dynamic_atlas::ChangeFlags
	{
		const auto data = this->m_atlas.add(glyphs.data(), static_cast<int>(glyphs.size()));

		this->update_texture(data);

		return data;
	}

	auto msdf_font::get_bitmap() const -> bitmap_const_ref
	{
		return this->m_bitmap;
	}

	auto msdf_font::update_texture(msdf_dynamic_atlas::ChangeFlags flags) -> void
	{
		static bool initialized = false;
		this->m_texture->bind();
		this->m_bitmap = bitmap_const_ref{ this->m_atlas.atlasGenerator().atlasStorage() };

		if (!initialized)
		{
			flags = msdf_dynamic_atlas::ChangeFlag::RESIZED;
			initialized = true;
		}

		switch (flags)
		{
			case msdf_dynamic_atlas::ChangeFlag::RESIZED:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexImage2D(GL_TEXTURE_2D,
					0,
					GL_RGB8,
					m_bitmap.width,
					m_bitmap.height,
					0,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					m_bitmap.pixels);
				break;
			case msdf_dynamic_atlas::ChangeFlag::REARRANGED:
				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glTexSubImage2D(GL_TEXTURE_2D,
					0,
					0,
					0,
					m_bitmap.width,
					m_bitmap.height,
					GL_RGB,
					GL_UNSIGNED_BYTE,
					m_bitmap.pixels);
				break;
			default: break;
		}
	}

	auto msdf_font::get_texture() const -> std::shared_ptr<sdlk2d::texture>
	{
		return this->m_texture;
	}

	msdf_font::~msdf_font()
	{
		msdfgen::destroyFont(this->m_font_handle);
	}

	auto msdf_font::make(std::string font_path) -> std::shared_ptr<msdf_font>
	{
		return std::make_shared<msdf_font>(std::move(font_path));
	}
}  // namespace sdlk