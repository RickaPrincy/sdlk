#pragma once

#include <SDL2/SDL.h>

#include <sdlk/core/window.hpp>
#include <string>

namespace sdlk
{
	class App : public Window
	{
	protected:
		const short _fps_limit = 16;
		void limit_fps(unsigned int limit);

	public:
		void run();
		void init_sdl_flags(Uint32 flags);

		App(std::string title,
			Size size,
			Position position = Position(SDL_WINDOWPOS_CENTERED),
			Uint32 flags = SDL_INIT_EVERYTHING);
		virtual ~App();
	};
}  // namespace sdlk
