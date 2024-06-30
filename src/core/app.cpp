#include <csignal>
#include <iostream>
#include <sdlk/core/app.hpp>
#include <stdexcept>

#include "../utils/check.hpp"

// TO handle ctrl + c or something else that can stop the application
static bool is_running = true;
static void signal_handler(int signal)
{
	is_running = false;
}

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
	std::cout << "destroy app" << std::endl;
	if (!sdlk::check::is_null(p_window))
	{
		delete p_window;
	}

	SDL_Quit();
}

void sdlk::App::run()
{
	std::signal(SIGINT, signal_handler);
	SDL_Event event;

	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT: is_running = false; break;
				default: break;	 // TODO: add event listener here
			}
		}

		this->p_window->render();
		this->limit_fps(SDL_GetTicks());
	}
}
