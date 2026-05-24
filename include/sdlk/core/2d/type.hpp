//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <glm/vec2.hpp>
#include <sdlk/core/color.hpp>
#include <vector>

namespace sdlk2d::type
{
	using point = glm::vec2;

	struct vertex
	{
		point m_uv{};
		point m_position{};
		sdlk::color m_color{};
	};

	using polygon = std::vector<vertex>;
}  // namespace sdlk2d::type
