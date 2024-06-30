#include <sdlk/core/app.hpp>
#include <stdexcept>

#include "../utils/check.hpp"

void sdlk::App::limit_fps(unsigned int limit)
{
	unsigned int ticks = SDL_GetTicks();

	if (limit < ticks)
		return;
	else if (limit > ticks + sdlk::App::FPS_LIMIT)
		SDL_Delay(sdlk::App::FPS_LIMIT);
	else
		SDL_Delay(limit - ticks);
}

void sdlk::App::init_sdl_flags(Uint32 flags)
{
	if (SDL_WasInit(flags) == 0)
	{
		return;
	}

	if (SDL_InitSubSystem(flags) != 0)
	{
		throw std::runtime_error("Cannot init sdl");
	}
}

void sdlk::App::quit_sdl_flags(Uint32 flags)
{
	if (SDL_WasInit(flags) != 0)
	{
		return;
	}

	SDL_QuitSubSystem(flags);
}

sdlk::App::App(std::string title, Size size, Position position, Uint32 flags)
{
	if (SDL_WasInit(flags) != 0 && SDL_Init(flags) != 0)
	{
		throw std::runtime_error("Cannot init sdl");
	}

	p_window = new Window(title, size, position, flags);
}

sdlk::App::~App()
{
	if (!sdlk::check::is_null(p_window))
	{
		delete p_window;
	}

	SDL_Quit();
}

void sdlk::App::run()
{
	bool is_running = true;
	SDL_Event event;

	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT: is_running = false; break;
				default: break;
			}
		}

		this->p_window->render();
		this->limit_fps(SDL_GetTicks());
	}
}
