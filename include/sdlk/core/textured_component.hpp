#pragma once

#include <SDL2/SDL_render.h>

#include <sdlk/core/component.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>

namespace sdlk
{
	class TexturedComponent : public Component
	{
	protected:
		SDL_Texture *p_sdl_texture = nullptr;
		virtual void render(SDL_Renderer *renderer) override;
		virtual void re_create_texture(SDL_Renderer *renderer) = 0;

	public:
		CP_GETTER(SDL_Texture, sdl_texture);
		TexturedComponent(Component *parent, Size size, Position position = Position());
		virtual ~TexturedComponent();
	};
}  // namespace sdlk
