#pragma once

#include <glm/glm.hpp>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk::quad
{
	auto make(int width, int height) -> std::vector<point>;

	auto indices() -> std::vector<uint32_t>;
}  // namespace sdlk::quad
