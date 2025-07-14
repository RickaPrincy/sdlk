#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>

#include <cstdint>
#include <functional>

namespace sdlk
{
	enum class event_type : std::uint8_t
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

	using event_callback = std::function<void(const SDL_Event &event)>;

	struct event_action
	{
		event_callback m_callback{};
		bool m_stop_propagation{ false };
	};

}  // namespace sdlk
