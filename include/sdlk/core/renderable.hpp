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
		SDL_Texture *p_sdl_texture = nullptr;
		SDL_Rect *p_src_rect = NULL;
		Renderable() = default;

	public:
		CP_GETTER(SDL_Texture, sdl_texture)

		virtual void render(SDL_Renderer *renderer);

		Renderable(Size size, Position position = Position(), SDL_Texture *texture = nullptr);
		virtual ~Renderable();
	};
}  // namespace sdlk
