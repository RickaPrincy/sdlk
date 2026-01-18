//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace sdlk2d::type
{
	using point= glm::vec2;
	using ring= std::vector<point>;

	using polygon = ring;
	using multi_polygon = std::vector<polygon>;
}
