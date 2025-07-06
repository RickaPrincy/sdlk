#pragma once

#include <array>
#include <vector>

namespace sdlk
{
	using point = std::array<float, 2>;
	using ring = std::vector<point>;
	using polygon = std::vector<ring>;
}  // namespace sdlk
