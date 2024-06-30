#pragma once

#include <SDL2/SDL.h>

#include <sdlk/core/box.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <string>

namespace sdlk
{
	class Window
	{
	protected:
		SDL_Renderer *p_sdl_renderer = nullptr;
		SDL_Window *p_sdl_window = nullptr;

	public:
		Size get_size() const;
		CP_GETTER(SDL_Window, sdl_window)
		CP_GETTER(SDL_Renderer, sdl_renderer)

		void render();

		Window(std::string title,
			Size size,
			Position position = Position(SDL_WINDOWPOS_CENTERED),
			Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
		virtual ~Window();
	};

}  // namespace sdlk
