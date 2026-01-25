//
// Created by ricka on 2026-01-18.
//

#include <sdlk/core/components/2d/fonts/msdf_font.hpp>
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

	auto msdf_font::load(const std::u32string &text) -> void
	{
		Charset charset{};
		for (const auto &c : text)
		{
			if (!this->is_loaded(c))
			{
				charset.add(c);
			}
		}

		if (charset.empty())
		{
			return;
		}

		return this->load(charset);
	}

	auto msdf_font::load(const char32_t &character) -> void
	{
		Charset charset{};
		charset.add(character);
		return this->load(charset);
	}

	auto msdf_font::load(const Charset &charset) -> void
	{
		const size_t old_size = m_glyphs_storage.size();

		this->m_font_geometry.loadCharset(this->m_font_handle, 1.0, charset);

		this->configure(old_size);
		this->add_to_atlas(old_size);

		for (size_t i = old_size; i < m_glyphs_storage.size(); ++i)
		{
			this->m_glyphs.emplace(static_cast<char32_t>(m_glyphs_storage[i].getCodepoint()),
				&this->m_glyphs_storage[i]);
		}
	}

	auto msdf_font::is_loaded(const char32_t &c) const -> bool
	{
		const auto &it = this->m_glyphs.find(c);
		return it != this->m_glyphs.end();
	}

	auto msdf_font::get(const char32_t &c) const
		-> std::optional<std::reference_wrapper<const GlyphGeometry>>
	{
		if (this->is_loaded(c))
		{
			return *this->m_glyphs.at(c);
		}

		return std::nullopt;
	}

	auto msdf_font::configure(const size_t start_index) -> void
	{
		for (size_t i = start_index; i < this->m_glyphs_storage.size(); ++i)
		{
			this->m_glyphs_storage[i].edgeColoring(
				&msdfgen::edgeColoringInkTrap, m_conf.m_max_corner_angle, 0);
			this->m_glyphs_storage[i].wrapBox(m_conf.m_glyph_scale,
				m_conf.m_pixel_range / m_conf.m_glyph_scale,
				m_conf.m_miter_limit);
		}
	}

	auto msdf_font::add_to_atlas(const size_t start_index) -> msdf_dynamic_atlas::ChangeFlags
	{
		std::vector<GlyphGeometry *> glyph_ptrs;
		glyph_ptrs.reserve(this->m_glyphs_storage.size() - start_index);

		for (size_t i = start_index; i < this->m_glyphs_storage.size(); ++i)
		{
			glyph_ptrs.push_back(&this->m_glyphs_storage[i]);
		}

		const auto data =
			this->m_atlas.add(*glyph_ptrs.data(), static_cast<int>(glyph_ptrs.size()));

		this->update_texture(data);

		return data;
	}

	auto msdf_font::get_bitmap() const -> bitmap_const_ref
	{
		return this->m_bitmap;
	}

	auto msdf_font::update_texture(msdf_dynamic_atlas::ChangeFlags flags) -> void
	{
		// TODO: fix
		static bool initialized = false;
		this->m_texture->bind();
		this->m_bitmap = bitmap_const_ref{ this->m_atlas.atlasGenerator().atlasStorage() };

		if (!initialized)
		{
			flags = msdf_dynamic_atlas::ChangeFlag::RESIZED;
			initialized = true;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		switch (flags)
		{
			case msdf_dynamic_atlas::ChangeFlag::RESIZED:
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

	auto msdf_font::get_conf() const -> msdf_font_conf
	{
		return this->m_conf;
	}

	auto msdf_font::make(std::string font_path) -> std::shared_ptr<msdf_font>
	{
		return std::make_shared<msdf_font>(std::move(font_path));
	}
}  // namespace sdlk