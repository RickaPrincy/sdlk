#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include <glm/glm.hpp>
#include <sdlk/core/events/event_listener.hpp>
#include <string>
#include <vector>

#include "sdlk/core/component.hpp"

namespace sdlk
{
	class app
	{
	private:
		Uint32 _frame_start = 0;

	protected:
		GLuint m_shader_program{};
		glm::vec2 m_size{};
		std::string m_title{};
		event_listener m_event_listener{};

		std::vector<component *> p_childs{};

		SDL_Window *p_window = nullptr;
		SDL_GLContext m_opengl_context = nullptr;

	public:
		app(std::string window_title,
			glm::vec2 window_size,
			Uint32 sdl_init_flags = SDL_INIT_EVERYTHING);

		auto run(int argc, char **argv) -> int;

		auto append_child(component *child) -> void;

		virtual auto limit_fps() -> void;

		virtual ~app();
	};
};	// namespace sdlk
