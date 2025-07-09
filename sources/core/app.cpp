#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <glad/glad.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sdlk/core/app.hpp>
#include <sdlk/core/opengl_utils.hpp>
#include <stdexcept>
#include <utility>

#include "static_resource.hpp"

namespace sdlk
{
	unsigned int app::s_window_width = 0;
	unsigned int app::s_window_height = 0;

	// TO handle ctrl + c or something else that can stop the application
	static bool is_running = true;
	static void signal_handler(int signal)
	{
		is_running = false;
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
						default:
							if (event.type == SDL_WINDOWEVENT &&
								event.window.event == SDL_WINDOWEVENT_RESIZED)
							{
								app::s_window_width = event.window.data1;
								app::s_window_height = event.window.data2;
								glViewport(0, 0, event.window.data1, event.window.data2);
							}

							this->m_event_listener.notify_event(event);
							break;
					}
				}

				glUseProgram(this->m_shader_program);

				// Update
				glClear(GL_COLOR_BUFFER_BIT);
				for (const auto &child : this->p_childs)
				{
					child->render(&this->m_shader_program);
				}
				SDL_GL_SwapWindow(this->p_window);

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

	app::app(std::string window_title,
		int width,
		int height,
		app_options options,
		Uint32 window_init_flags)
	{
		this->_frame_delay_ms = 1000 / options.fps;

		if (SDL_Init(window_init_flags) != 0)
		{
			throw std::runtime_error("Cannot init sdl");
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		this->p_window = SDL_CreateWindow(window_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

		app::s_window_width = std::move(width);
		app::s_window_height = std::move(height);

		this->m_title = std::move(window_title);
		this->m_opengl_context = SDL_GL_CreateContext(this->p_window);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			SDL_DestroyWindow(this->p_window);
			SDL_GL_DeleteContext(this->m_opengl_context);
			throw std::runtime_error("Failed to initialize GLAD");
		}

		options.vertex_source =
			options.vertex_source.empty() ? resource::s_vertex_source : options.vertex_source;

		options.fragment_source =
			options.fragment_source.empty() ? resource::s_fragment_source : options.fragment_source;

		this->m_shader_program = create_shader_program(
			std::move(options.vertex_source), std::move(options.fragment_source));
	}

	auto app::limit_fps() -> void
	{
		auto frame_time = SDL_GetTicks() - this->_frame_start;

		if (frame_time < this->_frame_delay_ms)
		{
			SDL_Delay(this->_frame_delay_ms - frame_time);
		}

		this->_frame_start = SDL_GetTicks();
	}

	auto app::append_child(component *child) -> void
	{
		this->p_childs.push_back(child);
	}

	auto app::get_width() -> int const
	{
		return app::s_window_width;
	}

	auto app::get_height() -> int const
	{
		return app::s_window_height;
	}

	auto app::get_event_listener() -> event_listener *const
	{
		return &this->m_event_listener;
	}

	app::~app()
	{
		if (this->m_shader_program)
		{
			glDeleteProgram(this->m_shader_program);
		}

		if (this->p_window)
		{
			SDL_DestroyWindow(this->p_window);
		}

		SDL_GL_DeleteContext(this->m_opengl_context);
		std::cout << "clean app\n";
	}
}  // namespace sdlk
