#pragma once

#include <SDL2/SDL.h>

#include <sdlk/core/component.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <string>

namespace sdlk
{
	class Window : public Component
	{
	protected:
		SDL_Renderer *p_sdl_renderer = nullptr;
		SDL_Window *p_sdl_window = nullptr;

		void render();

	public:
		CP_GETTER(SDL_Window, sdl_window)
		CP_GETTER(SDL_Renderer, sdl_renderer)

		Window(std::string title,
			Size size,
			Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
		virtual ~Window();

		friend class App;
	};

}  // namespace sdlk
