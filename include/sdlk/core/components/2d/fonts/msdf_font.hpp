//
// Created by ricka on 2026-01-18.
//

#pragma once

#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include <deque>
#include <memory>
#include <optional>
#include <sdlk/core/components/2d/shape/texture.hpp>

#define MIN_SIDE 256

namespace sdlk
{
	using namespace msdf_atlas;

	using charset = Charset;
	using font_geometry = FontGeometry;
	using glyph_geometry = GlyphGeometry;
	using font_handle = msdfgen::FontHandle;

	using bitmap = msdfgen::Bitmap<byte, 3>;
	using bitmap_ref = msdfgen::BitmapRef<byte, 3>;
	using bitmap_const_ref = msdfgen::BitmapConstRef<byte, 3>;
	using msdf_dynamic_atlas =
		DynamicAtlas<ImmediateAtlasGenerator<float, 3, msdfGenerator, BitmapAtlasStorage<byte, 3>>>;

	struct msdf_font_conf
	{
		const float m_pixel_range = 2.0;
		const float m_glyph_scale = 32.0;
		const float m_miter_limit = 1.0;
		const float m_max_corner_angle = 3.0;
	};

	struct glyph_storage
	{
		font_handle *m_font_handle{};
		std::vector<glyph_geometry> m_data{};
		font_geometry m_font_geometry{ &m_data };
		std::unordered_map<char32_t, glyph_geometry *> m_glyphs{};

		[[nodiscard]] auto size() const -> size_t;
		[[nodiscard]] auto is_loaded(const char32_t &character) const -> bool;
		[[nodiscard]] auto slice(size_t start_index) -> glyph_geometry *;
		[[nodiscard]] auto get(const char32_t &character) -> std::optional<std::reference_wrapper<const GlyphGeometry>>;

		auto invalidate_glyphs_map() -> void;
		auto load(const charset &charset) -> void;

		~glyph_storage();
	};

	class msdf_font final
	{
		msdf_font_conf m_conf{};
		bitmap_const_ref m_bitmap{};
		msdf_dynamic_atlas m_atlas{ 256 };

		bool m_texture_initialized{ false };
		std::shared_ptr<sdlk2d::texture> m_texture{};

		glyph_storage m_glyph_storage{ nullptr };

		auto update_texture(msdf_dynamic_atlas::ChangeFlags flags) -> void;
		auto add_to_atlas(size_t start_index) -> msdf_dynamic_atlas::ChangeFlags;

	public:
		explicit msdf_font(const std::string &font_path, msdf_font_conf &&conf = {});

		static auto make(const std::string &font_path) -> std::shared_ptr<msdf_font>;

		[[nodiscard]] auto get(const char32_t &c)
			-> std::optional<std::reference_wrapper<const GlyphGeometry>>;

		[[nodiscard]] auto get_conf() const -> msdf_font_conf;
		[[nodiscard]] auto get_bitmap() const -> bitmap_const_ref;
		[[nodiscard]] auto is_loaded(const char32_t &c) const -> bool;
		[[nodiscard]] auto get_texture() const -> std::shared_ptr<sdlk2d::texture>;

		auto load(const Charset &charset) -> void;
		auto load(const char32_t &character) -> void;
		auto load(const std::u32string &text) -> void;

		~msdf_font() = default;
	};
}  // namespace sdlk
