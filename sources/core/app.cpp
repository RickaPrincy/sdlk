#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL_image.h>
#include <glad/glad.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <stdexcept>

namespace sdlk
{
	unsigned int app::_s_window_width = 0;
	unsigned int app::_s_window_height = 0;

	// TO handle ctrl + c or something else that can stop the application
	static bool is_running = true;
	static void signal_handler(int signal)
	{
		is_running = false;
	}

	auto app::run(int, char **) -> int
	{
		std::signal(SIGINT, signal_handler);
		SDL_Event event;

		const auto ndc_background_color = this->_options.m_background.ndc();
		glClearColor(ndc_background_color.r,
			ndc_background_color.g,
			ndc_background_color.b,
			ndc_background_color.a);

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
								_s_window_width = event.window.data1;
								_s_window_height = event.window.data2;
								this->m_camera->update(get_width(), get_height());
								glViewport(0, 0, event.window.data1, event.window.data2);
							}

							this->m_event_listener->notify_event(event);
							break;
					}
				}

				// Update
				glClear(GL_COLOR_BUFFER_BIT);

				this->m_program->use();
				this->m_camera->load_uniforms(this->m_program);
				this->m_view->render(this->m_program);

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

	app::app(const std::string &window_title,
		const int &width,
		const int &height,
		const app_options &options,
		Uint32 window_init_flags)
		: observer(nullptr),
		  _options(options)
	{
		this->_frame_delay_ms = 1000 / this->_options.fps;

		if (SDL_Init(window_init_flags) != 0)
		{
			throw std::runtime_error("Cannot init sdl");
		}

		if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & IMG_INIT_JPG | IMG_INIT_PNG))
		{
			SDL_Quit();
			throw std::runtime_error("Cannot init sdl_image");
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

		_s_window_width = width;
		_s_window_height = height;

		this->m_opengl_context = SDL_GL_CreateContext(this->p_window);

		if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		{
			SDL_DestroyWindow(this->p_window);
			SDL_GL_DeleteContext(this->m_opengl_context);
			throw std::runtime_error("Failed to initialize GLAD");
		}

		this->m_program = gl_program::from_files(
			"resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
		this->m_event_listener = std::make_shared<event_listener>();
		this->m_view = std::make_shared<multiple_view>();
		this->m_camera = std::make_shared<camera>(get_width(), get_height());

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

	auto app::get_width() -> unsigned int
	{
		return _s_window_width;
	}

	auto app::get_height() -> unsigned int
	{
		return _s_window_height;
	}

	auto app::get_event_listener() -> std::shared_ptr<event_listener>
	{
		return this->m_event_listener;
	}

	auto app::add_view(const std::string &name, std::shared_ptr<renderable> child) const -> void
	{
		this->m_view->add_view(name, std::move(child));
		// TODO: remove
		this->m_view->switch_to(name);
	}

	app::~app()
	{
		if (this->p_window)
		{
			SDL_DestroyWindow(this->p_window);
		}

		SDL_GL_DeleteContext(this->m_opengl_context);

		IMG_Quit();
		SDL_Quit();
	}
}  // namespace sdlk
