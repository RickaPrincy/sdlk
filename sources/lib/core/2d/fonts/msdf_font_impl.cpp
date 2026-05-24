//
// Created by ricka on 2026-01-18.
//

#include <stdexcept>

#include "msdf_font_impl.hpp"
#include "free_type_handle_wrapper.hpp"

namespace sdlk2d
{
	glyph_storage::~glyph_storage()
	{
		msdfgen::destroyFont(this->m_font_handle);
	}

	auto glyph_storage::size() const -> size_t
	{
		return this->m_data.size();
	}

	auto glyph_storage::slice(const size_t start_index) -> glyph_geometry *
	{
		return &this->m_data[start_index];
	}

	auto glyph_storage::get(const char32_t &character)
		-> std::optional<std::reference_wrapper<const GlyphGeometry>>
	{
		if (this->is_loaded(character))
		{
			return *this->m_glyphs[character];
		}

		return std::nullopt;
	}

	auto glyph_storage::is_loaded(const char32_t &character) const -> bool
	{
		const auto &it = this->m_glyphs.find(character);
		return it != this->m_glyphs.end();
	}

	auto glyph_storage::load(const Charset &charset) -> void
	{
		this->m_font_geometry.loadCharset(this->m_font_handle, 1.0, charset);
	}

	auto glyph_storage::invalidate_glyphs_map() -> void
	{
		this->m_glyphs.clear();
		this->m_glyphs.reserve(this->m_data.size());

		for (auto &glyph : this->m_data)
		{
			this->m_glyphs.emplace(glyph.getCodepoint(), &glyph);
		}
	}

	msdf_font_impl::msdf_font_impl(const std::string &font_path, const msdf_font_conf conf) : m_conf(conf)
	{
		this->m_glyph_storage.m_font_handle =
			msdfgen::loadFont(free_type_handle_wrapper::instance()->raw(), font_path.c_str());

		if (!this->m_glyph_storage.m_font_handle)
		{
			throw std::runtime_error("Could not load font " + font_path);
		}

		this->m_texture = std::make_shared<sdlk::gl_texture>();
		glGenTextures(1, &this->m_texture->get_id());

		this->m_texture->bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		this->load(Charset::ASCII);
	}

	auto msdf_font_impl::load(const std::u32string &text) -> void
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

	auto msdf_font_impl::load(const char32_t &character) -> void
	{
		Charset charset{};
		charset.add(character);
		return this->load(charset);
	}

	auto msdf_font_impl::load(const Charset &charset) -> void
	{
		const size_t old_size = this->m_glyph_storage.size();

		this->m_glyph_storage.load(charset);

		this->add_to_atlas(old_size);

		this->m_glyph_storage.invalidate_glyphs_map();
	}

	auto msdf_font_impl::is_loaded(const char32_t &c) const -> bool
	{
		return this->m_glyph_storage.is_loaded(c);
	}

	auto msdf_font_impl::get(const char32_t &c)
		-> std::optional<std::reference_wrapper<const GlyphGeometry>>
	{
		return this->m_glyph_storage.get(c);
	}

	auto msdf_font_impl::add_to_atlas(const size_t start_index) -> msdf_dynamic_atlas::ChangeFlags
	{
		const auto storage_size = this->m_glyph_storage.size();
		const auto new_storage_size = storage_size - start_index;
		for (size_t i = start_index; i < storage_size; ++i)
		{
			this->m_glyph_storage.m_data[i].edgeColoring(
				&msdfgen::edgeColoringInkTrap, m_conf.m_max_corner_angle, 0);
			this->m_glyph_storage.m_data[i].wrapBox(m_conf.m_glyph_scale,
				m_conf.m_pixel_range / m_conf.m_glyph_scale,
				m_conf.m_miter_limit);
		}

		const auto data = this->m_atlas.add(
			this->m_glyph_storage.slice(start_index), static_cast<int>(new_storage_size), false);

		this->update_texture(data);

		return data;
	}

	auto msdf_font_impl::get_bitmap() const -> bitmap_const_ref
	{
		return this->m_bitmap;
	}

	auto msdf_font_impl::update_texture(const msdf_dynamic_atlas::ChangeFlags flags) -> void
	{
		this->m_texture->bind();
		this->m_bitmap = bitmap_const_ref{ this->m_atlas.atlasGenerator().atlasStorage() };

		const bool need_full_upload =
			!m_texture_initialized || flags & msdf_dynamic_atlas::ChangeFlag::RESIZED;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		if (need_full_upload)
		{
			glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RGB8,
				m_bitmap.width,
				m_bitmap.height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				m_bitmap.pixels);
			m_texture_initialized = true;
		}
		else
		{
			glTexSubImage2D(GL_TEXTURE_2D,
				0,
				0,
				0,
				m_bitmap.width,
				m_bitmap.height,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				m_bitmap.pixels);
		}
	}

	auto msdf_font_impl::get_texture() const -> std::shared_ptr<sdlk::gl_texture>
	{
		return this->m_texture;
	}

	auto msdf_font_impl::get_conf() const -> msdf_font_conf
	{
		return this->m_conf;
	}

	auto msdf_font_impl::get_metrics() const -> font_metrics
	{
		return this->m_glyph_storage.m_font_geometry.getMetrics();
	}

	auto msdf_font_impl::make(const std::string &font_path) -> std::shared_ptr<msdf_font_impl>
	{
		return std::make_shared<msdf_font_impl>(font_path);
	}
}  // namespace sdlk