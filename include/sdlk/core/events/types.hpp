#pragma once

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_stdinc.h>

#include <cstdint>
#include <functional>

namespace sdlk
{
	enum class event_type : std::uint8_t
	{
		key_down,
		key_up,
		window_event,
		mouse_motion,
		mouse_wheel,
		mouse_button_down,
		mouse_button_up,
		all,
	};

	using event_callback = std::function<void(const SDL_Event &event)>;

	struct event_action
	{
		event_callback m_callback{};
		bool m_stop_propagation{ false };
	};

}  // namespace sdlk
