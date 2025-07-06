#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <glad/glad.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sdlk/core/sdl_resource_wrapper.hpp>
#include <sdlk/sdlk.hpp>
#include <stdexcept>
#include <utility>

namespace sdlk
{
	static constexpr int TARGET_FPS = 30;
	static constexpr int FRAME_DELAY_MS = 1000 / TARGET_FPS;

	// TO handle ctrl + c or something else that can stop the application
	static bool is_running = true;
	static void signal_handler(int signal)
	{
		is_running = false;
	}

	auto app::limit_fps() -> void
	{
		Uint32 frame_time = SDL_GetTicks() - this->_frame_start;

		if (frame_time < FRAME_DELAY_MS)
		{
			SDL_Delay(FRAME_DELAY_MS - frame_time);
		}

		this->_frame_start = SDL_GetTicks();
	}

	auto app::run(int argc, char **argv) -> int
	{
		std::signal(SIGINT, signal_handler);
		SDL_Event event;

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		try
		{
			while (is_running)
			{
				// Event
				while (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
						case SDL_QUIT: is_running = false; break;
						default: this->m_event_listener.notify_event(event); break;
					}
				}

				// Update
				glClear(GL_COLOR_BUFFER_BIT);
				SDL_GL_SwapWindow(this->m_window.get());

				// FPS Limit
				this->limit_fps();
			}
		}
		catch (const std::runtime_error &e)
		{
			std::cerr << "[ ERROR ] : " << e.what() << "\n";
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
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
		this->m_opengl_context = SDL_GL_CreateContext(this->m_window.get());

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			SDL_GL_DeleteContext(this->m_opengl_context);
			throw std::runtime_error("Failed to initialize GLAD");
		}
	}

	app::~app()
	{
		SDL_GL_DeleteContext(this->m_opengl_context);
	}
}  // namespace sdlk
