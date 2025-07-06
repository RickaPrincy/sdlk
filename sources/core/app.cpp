#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <glad/glad.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <sdlk/sdlk.hpp>
#include <stdexcept>
#include <utility>

namespace sdlk
{
	static constexpr int TARGET_FPS = 30;
	static constexpr int FRAME_DELAY_MS = 1000 / TARGET_FPS;

	static const char *vertex_shader_src = R"glsl(
#version 330 core

layout(location = 0) in vec2 aPos;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)glsl";

	static const char *fragment_shader_src = R"glsl(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.4, 0.7, 0.9, 1.0);
}
)glsl";

	GLuint compile_shader(GLenum type, const char *source)
	{
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		GLint success{};
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Shader compilation failed: ") + infoLog);
		}
		return shader;
	}

	GLuint create_shader_program(const char *vertex_src, const char *fragment_src)
	{
		GLuint vertexShader = compile_shader(GL_VERTEX_SHADER, vertex_src);
		GLuint fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragment_src);

		GLuint program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		GLint success{};
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Program linking failed: ") + infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
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
						default: this->m_event_listener.notify_event(event); break;
					}
				}

				glUseProgram(this->m_shader_program);

				// Update
				glClear(GL_COLOR_BUFFER_BIT);
				for (const auto &child : this->p_childs)
				{
					child->draw();
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

	app::app(std::string window_title, glm::vec2 window_size, Uint32 window_init_flags)
	{
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
			window_size.x,
			window_size.y,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

		this->m_size = window_size;
		this->m_title = std::move(window_title);
		this->m_opengl_context = SDL_GL_CreateContext(this->p_window);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		{
			SDL_DestroyWindow(this->p_window);
			SDL_GL_DeleteContext(this->m_opengl_context);
			throw std::runtime_error("Failed to initialize GLAD");
		}

		this->m_shader_program = create_shader_program(vertex_shader_src, fragment_shader_src);
	}

	auto app::append_child(component *child) -> void
	{
		child->_window_size = this->m_size;
		this->p_childs.push_back(child);
	}

	app::~app()
	{
		if (this->m_shader_program != 0)
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
