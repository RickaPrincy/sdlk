#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include <glm/glm.hpp>
#include <sdlk/core/component.hpp>
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

		std::vector<component *> p_childs{};

		SDL_Window *p_window = nullptr;
		SDL_GLContext m_opengl_context = nullptr;
		auto append_child(component *child) -> void;

	public:
		app(std::string window_title,
			int width,
			int height,
			Uint32 sdl_init_flags = SDL_INIT_EVERYTHING);

		auto run(int argc, char **argv) -> int;

		[[nodiscard]] auto get_width() -> int const;
		[[nodiscard]] auto get_height() -> int const;
		[[nodiscard]] auto get_event_listener() -> event_listener *const;

		virtual auto limit_fps() -> void;

		virtual ~app();
		friend class component;
	};
};	// namespace sdlk
