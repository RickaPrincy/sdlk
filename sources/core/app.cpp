#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sdlk/core/sdl_resource_wrapper.hpp>
#include <sdlk/sdlk.hpp>
#include <stdexcept>
#include <utility>

namespace sdlk
{
	const static short FPS_LIMIT = 16;

	// TO handle ctrl + c or something else that can stop the application
	static bool is_running = true;
	static void signal_handler(int signal)
	{
		is_running = false;
	}

	void sdlk::app::limit_fps(unsigned int limit)
	{
		unsigned int ticks = SDL_GetTicks();

		if (limit < ticks)
		{
			return;
		}
		else if (limit > ticks + FPS_LIMIT)
		{
			SDL_Delay(FPS_LIMIT);
		}
		else
		{
			SDL_Delay(limit - ticks);
		}
	}

	app::app(std::string window_title, size window_size, Uint32 window_init_flags)
	{
		if (SDL_Init(window_init_flags) != 0)
		{
			throw std::runtime_error("Cannot init sdl");
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		auto window = SDL_CreateWindow(window_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			window_size.m_width,
			window_size.m_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

		this->m_size = window_size;
		this->m_title = std::move(window_title);
		this->m_window = make_sdl_resource_shared(window, SDL_DestroyWindow);
	}

	auto app::run(int argc, char **argv) -> int
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
						default: this->m_event_listener.notify_event(event); break;
					}
				}

				this->limit_fps(SDL_GetTicks());
			}
		}
		catch (const std::runtime_error &e)
		{
			std::cerr << "[ ERROR ] : " << e.what() << "\n";
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}
}  // namespace sdlk
