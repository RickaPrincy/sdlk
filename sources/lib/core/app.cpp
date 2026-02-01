#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL_image.h>
#include <glad/glad.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sdlk/core/app.hpp>
#include <sdlk/core/events/event_listener.hpp>
#include <stdexcept>

#include "imgui/imgui_wrapper.hpp"

namespace sdlk
{
	// TO handle ctrl + c or something else that can stop the application
	static bool is_running = true;
	static void signal_handler(int signal)
	{
		is_running = false;
	}

	app::app(const std::string &window_title,
		const int &width,
		const int &height,
		const app_options &options,
		const Uint32 sdl_init_flags)
		: _options(options)
	{
		this->_frame_delay_ms = 1000 / this->_options.m_fps;

		if (SDL_Init(sdl_init_flags) != 0)
		{
			throw std::runtime_error("Cannot init sdl");
		}

		if ((IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) & (IMG_INIT_JPG | IMG_INIT_PNG)) == 0)
		{
			SDL_Quit();
			throw std::runtime_error("Cannot init sdl_image");
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		const auto dpi_scale = 1;
		const auto window_width = static_cast<int>(static_cast<float>(width) * dpi_scale);
		const auto window_height = static_cast<int>(static_cast<float>(height) * dpi_scale);

		this->p_window = SDL_CreateWindow(window_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			window_width,
			window_height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

		this->m_opengl_context = SDL_GL_CreateContext(this->p_window);

		if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		{
			SDL_DestroyWindow(this->p_window);
			SDL_GL_DeleteContext(this->m_opengl_context);
			IMG_Quit();
			SDL_Quit();
			throw std::runtime_error("Failed to initialize GLAD");
		}

		SDL_GL_MakeCurrent(p_window, m_opengl_context);
		if (this->_options.m_vsync)
		{
			SDL_GL_SetSwapInterval(1);
		}

		this->_imgui_wrapper =
			std::make_shared<imgui_wrapper>(p_window, &m_opengl_context, "#version 330 core");
		this->m_view = std::make_shared<multiple_view>();
		this->m_program = gl_program::from_files(
			"resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
		this->m_camera = std::make_shared<camera>(window_width, window_height);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glViewport(0, 0, window_width, window_height);
	}

	auto app::handle_event(SDL_Event &event) const -> void
	{
		while (SDL_PollEvent(&event))
		{
			imgui_wrapper::process_event(event);

			switch (event.type)
			{
				case SDL_QUIT: is_running = false; break;
				default:
					if (event.type == SDL_WINDOWEVENT &&
						event.window.event == SDL_WINDOWEVENT_CLOSE &&
						event.window.windowID == SDL_GetWindowID(p_window))
					{
						is_running = false;
						break;
					}

					if (event.type == SDL_WINDOWEVENT &&
						event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						const int width = event.window.data1;
						const int height = event.window.data2;

						this->m_camera->update(width, height);
						glViewport(0, 0, width, height);
					}

					event_listener::instance()->notify_event(event);
					break;
			}
		}
	}

	auto app::run(int, char **) -> int
	{
		std::signal(SIGINT, signal_handler);

		const auto ndc_background_color = this->_options.m_background.ndc();
		glClearColor(ndc_background_color.r,
			ndc_background_color.g,
			ndc_background_color.b,
			ndc_background_color.a);

		try
		{
			SDL_Event event;
			this->_frame_start = SDL_GetTicks();
			while (is_running)
			{
				this->handle_event(event);

				glClear(GL_COLOR_BUFFER_BIT);

				imgui_wrapper::new_frame();

				{
					static float f = 0.0f;
					static int counter = 0;

					ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

					ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

					ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

					if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
						counter++;
					ImGui::SameLine();
					ImGui::Text("counter = %d", counter);
					ImGui::End();
				}

				this->m_program->use();
				this->m_camera->load_uniforms(this->m_program);
				this->m_view->render(this->m_program);

				imgui_wrapper::render();
				imgui_wrapper::draw();

				SDL_GL_SwapWindow(this->p_window);

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

	auto app::limit_fps() -> void
	{
		auto frame_time = SDL_GetTicks() - this->_frame_start;

		if (frame_time < this->_frame_delay_ms)
		{
			SDL_Delay(this->_frame_delay_ms - frame_time);
		}

		this->_frame_start = SDL_GetTicks();
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
