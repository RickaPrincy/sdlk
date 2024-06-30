#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>

#include <functional>

namespace sdlk
{
	// TODO: create custom enum
	using EventType = Uint32;
	using EventCallback = std::function<void(const SDL_Event &event)>;

	struct EventAction
	{
		EventCallback m_callback;
		bool m_stop_propagation;
	};

}  // namespace sdlk
