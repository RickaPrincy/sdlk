//
// Created by ricka on 2026-01-18.
//

#pragma once

#include <memory>
#include <optional>
#include <sdlk/core/color.hpp>
#include <sdlk/core/components/2d/shape/texture.hpp>

namespace sdlk2d
{
	struct text_style
	{
		float m_size{ 0.2 };
		sdlk::color m_fg_color{ sdlk::color::white() };
		sdlk::color m_bg_color{ SDL_Color{ .r = 0, .g = 0, .b = 0, .a = 0 } };
	};

	struct shape_style
	{
		enum class type
		{
			uniform,
			vertex,
			texture,
		};

		type m_type{ type::uniform };
		std::shared_ptr<texture> m_texture{};
		std::optional<sdlk::color> m_uniform_color{};

		explicit shape_style()
		{
			this->m_type = type::vertex;
		}

		explicit shape_style(const sdlk::color &color)
		{
			this->m_type = type::uniform;
			this->m_uniform_color = color;
		}

		explicit shape_style(const std::shared_ptr<texture> &texture)
		{
			this->m_type = type::texture;
			this->m_texture = texture;
		}
	};
}  // namespace sdlk2d