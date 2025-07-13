#pragma once

#include <SDL2/SDL_pixels.h>

#include <array>
#include <glm/vec2.hpp>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk::converter
{
	auto sdl_color_to_ndc(SDL_Color color) -> std::array<float, 4>;

	auto pixel_point_to_ndc(const point& pixel, const int& window_width, const int& window_height)
		-> point;

	auto pixels_points_to_ndcs(const std::vector<point>& pixels,
		const int& window_width,
		const int& window_height) -> std::vector<point>;

	auto pixel_offset_to_ndc(const glm::vec2& pixels,
		const int& window_width,
		const int& window_height) -> glm::vec2;

	auto pixel_scale_to_ndc(const glm::vec2& pixel,
		const int& window_width,
		const int& window_height) -> glm::vec2;
}  // namespace sdlk::converter
