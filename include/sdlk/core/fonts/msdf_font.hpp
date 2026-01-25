//
// Created by ricka on 2026-01-18.
//

#pragma once

#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include <memory>
#include <sdlk/core/components/2d/shape/texture.hpp>

namespace sdlk
{
	using namespace msdf_atlas;
	using msdf_dynamic_atlas =
		DynamicAtlas<ImmediateAtlasGenerator<float, 3, msdfGenerator, BitmapAtlasStorage<byte, 3>>>;
	using bitmap = msdfgen::Bitmap<byte, 3>;
	using bitmap_ref = msdfgen::BitmapRef<byte, 3>;
	using bitmap_const_ref = msdfgen::BitmapConstRef<byte, 3>;

	struct msdf_font_conf
	{
		const float m_pixel_range = 2.0;
		const float m_glyph_scale = 32.0;
		const float m_miter_limit = 1.0;
		const float m_max_corner_angle = 3.0;
	};

	class msdf_font final
	{
		msdf_font_conf m_conf{};
		std::string m_font_path{};
		bitmap_const_ref m_bitmap{};
		msdf_dynamic_atlas m_atlas{};
		msdfgen::FontHandle *m_font_handle{};
		std::shared_ptr<sdlk2d::texture> m_texture{};
		std::unordered_map<char32_t, GlyphGeometry> m_glyphs{};

		auto configure(GlyphGeometry &glyph) const -> GlyphGeometry;
		auto update_texture(msdf_dynamic_atlas::ChangeFlags flags) -> void;
		auto add_to_atlas(std::vector<GlyphGeometry> &glyphs) -> msdf_dynamic_atlas::ChangeFlags;

	public:
		explicit msdf_font(std::string font_path, msdf_font_conf &&conf = {});

		static auto make(std::string font_path) -> std::shared_ptr<msdf_font>;

		[[nodiscard]] auto get(const char32_t &c) -> const GlyphGeometry &;
		[[nodiscard]] auto get_texture() const -> std::shared_ptr<sdlk2d::texture>;
		[[nodiscard]] auto get_bitmap() const -> bitmap_const_ref;
		[[nodiscard]] auto get_conf() const -> msdf_font_conf;

		auto load(const Charset &charset) -> void;
		auto load(const char32_t &character) -> void;

		~msdf_font();
	};
}  // namespace sdlk
