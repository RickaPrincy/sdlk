#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include <glm/glm.hpp>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <string>
#include <vector>

namespace sdlk
{
	class app
	{
	private:
		Uint32 _frame_start = 0;

	protected:
		int m_width{}, m_height{};
		GLuint m_shader_program{};
		std::string m_title{};
		event_listener m_event_listener{};

		std::vector<shape *> p_childs{};

		SDL_Window *p_window = nullptr;
		SDL_GLContext m_opengl_context = nullptr;

	public:
		app(std::string window_title,
			int width,
			int height,
			Uint32 sdl_init_flags = SDL_INIT_EVERYTHING);

		auto run(int argc, char **argv) -> int;
		auto append_child(shape *child) -> void;

		[[nodiscard]] auto get_width() -> int const;
		[[nodiscard]] auto get_height() -> int const;

		virtual auto limit_fps() -> void;

		virtual ~app();
	};
};	// namespace sdlk
