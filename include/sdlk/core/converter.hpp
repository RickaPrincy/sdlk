#pragma once

#include <SDL2/SDL_pixels.h>

#include <array>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk::converter
{
	auto sdl_color_to_ndc(SDL_Color color) -> std::array<float, 4>;
	auto pixel_uv_to_ndc(std::vector<point> pixels, int texture_width, int texture_height)
		-> std::vector<point>;
}  // namespace sdlk::converter
