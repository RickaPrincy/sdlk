#pragma once

#include <glm/vec2.hpp>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk::converter
{
	auto pixel_position_to_ndc(const glm::vec2& pixel,
		const int& window_width,
		const int& window_height) -> glm::vec2;

	auto pixels_position_to_ndc(const std::vector<glm::vec2>& pixels,
		const int& window_width,
		const int& window_height) -> std::vector<glm::vec2>;

	auto pixel_offset_to_ndc(const glm::vec2& pixels,
		const int& window_width,
		const int& window_height) -> glm::vec2;

	auto pixel_scale_to_ndc(const glm::vec2& pixel,
		const int& window_width,
		const int& window_height) -> glm::vec2;
}  // namespace sdlk::converter
