#pragma once

#include <SDL2/SDL.h>

#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/window.hpp>
#include <string>

namespace sdlk
{
	class App
	{
	protected:
		const static short FPS_LIMIT = 16;
		Window *p_window = nullptr;
		void limit_fps(unsigned int limit);

	public:
		CP_GETTER(Window, window)
		void run();
		void init_sdl_flags(Uint32 flags);
		void quit_sdl_flags(Uint32 flags);

		App(std::string title,
			Size size,
			Position position = Position(SDL_WINDOWPOS_CENTERED),
			Uint32 flags = SDL_INIT_EVERYTHING);
		virtual ~App();
	};
}  // namespace sdlk
