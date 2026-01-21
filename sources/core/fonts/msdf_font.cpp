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

		this->load(Charset::ASCII);
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
	}

	auto msdf_font::get(const char &c) -> const GlyphGeometry &
	{
		const auto &it = this->m_glyphs.find(c);
		if (it != this->m_glyphs.end())
		{
			return it->second;
		}

		throw std::runtime_error("Not implemented");
	}

	auto msdf_font::configure(GlyphGeometry &glyph) const -> GlyphGeometry
	{
		glyph.edgeColoring(&msdfgen::edgeColoringInkTrap, m_conf.m_max_corner_angle, 0);
		glyph.wrapBox(m_conf.m_glyph_scale,
			m_conf.m_pixel_range / m_conf.m_glyph_scale,
			m_conf.m_miter_limit);

		return glyph;
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