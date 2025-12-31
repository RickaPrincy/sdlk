//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <SDL_pixels.h>

#include <sdlk/core/renderable/renderable.hpp>
#include <sdlk/core/renderable/type.hpp>

namespace sdlk
{
	class colored_shape: public renderable
	{
	protected:
		SDL_Color m_color{};

	public:
		explicit colored_shape(const type::polygon &polygon, SDL_Color color);

		auto render(const std::shared_ptr<gl_program> &program) -> void override;

		~colored_shape() override = default;
	};
}