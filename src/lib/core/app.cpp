#include <SDL2/SDL_events.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sdlk/core/app.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

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
	}
	catch (const std::runtime_error &error)
	{
		// TODO: refactor
		std::cerr << error.what() << std::endl;
		delete p_window;
		SDL_Quit();
		exit(EXIT_FAILURE);
	}

	p_window->p_event_listener = &m_event_listener;
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
				default: m_event_listener.notify_event(event); break;
			}
		}

		this->p_window->render();
		this->limit_fps(SDL_GetTicks());
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
