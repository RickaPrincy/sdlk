//
// Created by ricka on 2026-01-18.
//

#pragma once

#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include <memory>

namespace sdlk
{
	using namespace msdf_atlas;
	using msdf_dynamic_atlas =
		DynamicAtlas<ImmediateAtlasGenerator<float, 3, msdfGenerator, BitmapAtlasStorage<byte, 3>>>;

	struct msdf_font_conf
	{
		const double m_pixel_range = 2.0;
		const double m_glyph_scale = 32.0;
		const double m_miter_limit = 1.0;
		const double m_max_corner_angle = 3.0;
	};

	class msdf_font final
	{
		msdf_font_conf m_conf{};
		std::string m_font_path{};
		msdfgen::FontHandle* m_font_handle{};
		std::unordered_map<char, GlyphGeometry> m_glyphs{};

		auto configure(GlyphGeometry &glyph) const -> GlyphGeometry;

	public:
		explicit msdf_font(std::string font_path, msdf_font_conf&& conf = {});

		static auto make(std::string font_path) -> std::shared_ptr<msdf_font>;

		auto load(const Charset &charset) -> void;

		[[nodiscard]] auto get(const char &c) -> const GlyphGeometry&;

		~msdf_font();
	};
}  // namespace sdlk
