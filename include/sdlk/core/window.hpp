#pragma once

#include <SDL2/SDL.h>

#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/renderable.hpp>
#include <string>

namespace sdlk
{
	class Window : private Renderable
	{
	private:
		void render();

	protected:
		SDL_Renderer *p_sdl_renderer = nullptr;
		SDL_Window *p_sdl_window = nullptr;

	public:
		Size get_size() const;
		CP_GETTER(SDL_Window, sdl_window)
		CP_GETTER(SDL_Renderer, sdl_renderer)

		Window(std::string title,
			Size size,
			Position position = Position(SDL_WINDOWPOS_CENTERED),
			Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
		virtual ~Window();

		friend class App;
	};

}  // namespace sdlk
