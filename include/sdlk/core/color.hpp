//
// Created by ricka on 2026-01-25.
//
#pragma once

#include <SDL_pixels.h>

#include <glm/vec4.hpp>
#include <sdlk/core/converter.hpp>

namespace sdlk
{
	struct color
	{
		SDL_Color m_sdl_color{};
		glm::vec4 m_ndc_color{};

		explicit color(const SDL_Color& color)
		{
			this->m_sdl_color = color;
			this->m_ndc_color = converter::sdl_color_to_ndc(color);
		}

		[[nodiscard]] auto ndc() const -> glm::vec4
		{
			return this->m_ndc_color;
		}

		color() = default;
		color(const color&) = default;
		color(color&&) noexcept = default;
		color& operator=(const color&) = default;
		color& operator=(color&&) noexcept = default;

		static color red()
		{
			return color(SDL_Color{ .r = 255, .g = 0, .b = 0, .a = 255 });
		}

		static color green()
		{
			return color(SDL_Color{ .r = 0, .g = 255, .b = 0, .a = 255 });
		}

		static color blue()
		{
			return color(SDL_Color{ .r = 0, .g = 0, .b = 255, .a = 255 });
		}

		static color black()
		{
			return color(SDL_Color{ .r = 0, .g = 0, .b = 0, .a = 255 });
		}

		static color white()
		{
			return color(SDL_Color{ .r = 255, .g = 255, .b = 255, .a = 255 });
		}
	};
}  // namespace sdlk
