#pragma once

#include <glm/vec2.hpp>
#include <vector>

namespace sdlk
{
	auto pixel_to_ndc(const glm::vec2& pixel, const glm::vec2& window_size) -> glm::vec2;
	auto pixels_to_ndc(const std::vector<glm::vec2>& pixels, const glm::vec2& window_size)
		-> std::vector<glm::vec2>;
}  // namespace sdlk
