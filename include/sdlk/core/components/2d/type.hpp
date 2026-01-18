//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <SDL_pixels.h>

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
		std::optional<SDL_Color> m_color{};

		explicit vertex(const point &position)
		{
			this->m_position = position;
		}

		explicit vertex(const point &position, const point &uv)
		{
			this->m_uv = uv;
			this->m_position = position;
		}

		explicit vertex(const point &position, const SDL_Color &color)
		{
			this->m_color = color;
			this->m_position = position;
		}
	};

	using polygon = std::vector<vertex>;
}
