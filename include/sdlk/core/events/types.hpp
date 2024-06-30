#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>

#include <functional>

namespace sdlk
{
	enum class EventType
	{
		KEY_DOWN,
		KEY_UP,
		WINDOW_EVENT,
		MOUSE_MOTION,
		MOUSE_WHEEL,
		MOUSE_BUTTON_DOWN,
		MOUSE_BUTTON_UP,
		NOT_SUPPORTED,
	};

	using EventCallback = std::function<void(const SDL_Event &event)>;

	struct EventAction
	{
		EventCallback m_callback;
		bool m_stop_propagation;
	};

}  // namespace sdlk
