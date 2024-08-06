#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sdlk/core/app.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>
#include <string>

// TO handle ctrl + c or something else that can stop the application
static bool is_running = true;
static void signal_handler(int signal)
{
	is_running = false;
}

namespace sdlk
{
	static void quit_resources(sdlk::Window *window)
	{
		if (!sdlk::check::is_null(window))
		{
			delete window;
		}

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}
}  // namespace sdlk

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
	sdlk::throw_if_not_success(SDL_InitSubSystem(flags), "Cannot init SDL");
}

void sdlk::App::quit_sdl_flags(Uint32 flags)
{
	if (SDL_WasInit(flags) != 0)
	{
		return;
	}

	SDL_QuitSubSystem(flags);
}

sdlk::App::App(std::string title, Size size, Uint32 flags)
{
	if (SDL_WasInit(flags) != 0)
	{
		sdlk::throw_if_not_success(SDL_Init(flags), "Cannot init SDL");
	}
	try
	{
		p_window = new Window(title, size, flags);
		const auto image_init_status = IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_JXL |
												IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_AVIF);

		if (image_init_status == 0)
		{
			throw std::runtime_error("Cannot init sdl image");
		}

		if (TTF_Init() == -1)
		{
			throw std::runtime_error("Cannot init sdl ttf");
		}
	}
	catch (const std::runtime_error &error)
	{
		// TODO: refactor
		std::cerr << error.what() << std::endl;
		sdlk::quit_resources(p_window);
		exit(EXIT_FAILURE);
	}

	p_window->p_event_listener = &m_event_listener;
}

sdlk::App::~App()
{
	sdlk::quit_resources(p_window);
}

void sdlk::App::run()
{
	std::signal(SIGINT, signal_handler);
	SDL_Event event;

	try
	{
		while (is_running)
		{
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_QUIT: is_running = false; break;
					default: m_event_listener.notify_event(event); break;
				}
			}
			this->p_window->render();
			this->limit_fps(SDL_GetTicks());
		}
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << "[ ERROR ] : " << e.what() << std::endl;
	}
}

void sdlk::App::append_child(sdlk::Component *component)
{
	this->p_window->append_child(component);
}

sdlk::Window *sdlk::App::get_window()
{
	return p_window;
}
