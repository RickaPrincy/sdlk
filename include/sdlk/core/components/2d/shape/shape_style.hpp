//
// Created by ricka on 2026-01-18.
//

#pragma once

#include <SDL_pixels.h>

#include <glm/vec4.hpp>
#include <memory>
#include <optional>
#include <sdlk/core/components/2d/shape/texture.hpp>
#include <sdlk/core/converter.hpp>

namespace sdlk2d
{
	struct shape_style
	{
		enum class type
		{
			uniform, vertex, texture
		};

		type m_type{type::uniform};
		std::shared_ptr<texture> m_texture{};
		std::optional<SDL_Color> m_uniform_color{};
		std::optional<glm::vec4> m_ndc_uniform_color{};

		explicit shape_style()
		{
			this->m_type = type::vertex;
		}

		explicit shape_style(const SDL_Color &uniform_color)
		{
			this->m_type = type::uniform;
			this->m_uniform_color = uniform_color;
			this->m_ndc_uniform_color = sdlk::converter::sdl_color_to_ndc(uniform_color);
		}

		explicit shape_style(const std::shared_ptr<texture> &texture)
		{
			this->m_type = type::texture;
			this->m_texture = texture;
		}
	};
}