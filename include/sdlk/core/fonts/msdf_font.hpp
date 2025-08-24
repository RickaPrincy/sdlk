//
// Created by ricka on 24/08/25.
//

#pragma once

#include <msdf-atlas-gen/msdf-atlas-gen.h>

#include <memory>
#include <unordered_map>

namespace  sdlk
{
	using namespace msdf_atlas;
	using msdf_dynamic_atlas = DynamicAtlas<ImmediateAtlasGenerator<float, 3, msdfGenerator, BitmapAtlasStorage<byte, 3>>>;

	struct msdf_font_conf
	{
		const double pixel_range = 2.0;
		const double glyph_scale = 32.0;
		const double miter_limit = 1.0;
		const double max_corner_angle = 3.0;
	};

	class msdf_font final
	{
		msdf_font_conf _conf{};
		std::string _font_path{};
		msdf_dynamic_atlas _atlas{};
		std::unordered_map<char, GlyphGeometry> _glyphs_map{};

		msdfgen::FontHandle *_font_handle{nullptr};

		auto load(char c) -> const GlyphGeometry&;
		auto bind_and_clone(GlyphGeometry &glyph) const -> GlyphGeometry;
	public:
		explicit msdf_font(std::string font_path, msdf_font_conf &&conf = {});

		[[nodiscard]] auto get(char c) -> const GlyphGeometry&;
		[[nodiscard]] auto atlas() -> msdf_dynamic_atlas&;

		static auto make(std::string font_path) -> std::shared_ptr<msdf_font>;

		~msdf_font();
	};
}