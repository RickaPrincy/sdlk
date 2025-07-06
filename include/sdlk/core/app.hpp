#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include <memory>
#include <sdlk/core/events/event_listener.hpp>
#include <string>

#include "properties.hpp"

namespace sdlk
{
	class app
	{
	protected:
		size m_size{};
		std::string m_title{};
		event_listener m_event_listener{};
		std::shared_ptr<SDL_Window> m_window = nullptr;

	public:
		app(std::string window_title,
			size window_size,
			Uint32 sdl_init_flags = SDL_INIT_EVERYTHING);

		auto run(int argc, char **argv) -> int;
		virtual auto limit_fps(unsigned int limit) -> void;
	};
};	// namespace sdlk
