#pragma once

#include <SDL2/SDL_render.h>

#include <sdlk/core/box.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>

namespace sdlk
{
	class Renderable : public Box
	{
	protected:
		SDL_Texture *p_sdl_texture = nullptr;
		Renderable() = default;

	public:
		CP_GETTER(SDL_Texture, sdl_texture)

		virtual void render(SDL_Renderer *renderer);

		Renderable(SDL_Texture *texture);
		virtual ~Renderable();
	};
}  // namespace sdlk
