#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include <sdlk/core/box.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>

namespace sdlk
{
	class Renderable : public Box
	{
	protected:
		SDL_Rect m_src_rect{ 0, 0, -1, -1 };
		Renderable() = default;

	public:
		virtual void render(SDL_Renderer *renderer) = 0;
		Renderable(Size size, Position position = Position());
	};
}  // namespace sdlk
