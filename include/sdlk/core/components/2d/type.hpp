//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <glm/glm.hpp>
#include <optional>
#include <vector>

namespace sdlk2d::type
{
	using point = glm::vec2;

	struct vertex
	{
		point m_position{};
		std::optional<point> m_uv{};
		std::optional<sdlk::color> m_color{};

		explicit vertex(const point &position)
		{
			this->m_position = position;
		}

		explicit vertex(const point &position, const point &uv)
		{
			this->m_uv = uv;
			this->m_position = position;
		}

		explicit vertex(const point &position, const sdlk::color &color)
		{
			this->m_color = color;
			this->m_position = position;
		}
	};

	using polygon = std::vector<vertex>;
	using points = std::vector<point>;
}  // namespace sdlk2d::type
