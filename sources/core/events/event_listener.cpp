#include <SDL2/SDL_events.h>

#include <sdlk/core/events/event_listener.hpp>

namespace sdlk
{
	auto event_listener::notify_event(const SDL_Event &event) -> void
	{
		const auto actual_type = get_event_type_value(event);
		std::vector<event_action> actions{};

		for (const auto &[etype, actionList] : m_event_listeners)
		{
			if (etype == actual_type || etype == event_type::all)
			{
				actions.insert(actions.end(), actionList.begin(), actionList.end());
			}
		}

		for (const auto &action : actions)
		{
			action.m_callback(event);
			if (action.m_stop_propagation)
			{
				break;
			}
		};
	}

	auto event_listener::get_event_type_value(const SDL_Event &event) -> event_type
	{
		switch (event.type)
		{
			case SDL_KEYDOWN: return event_type::key_down;
			case SDL_KEYUP: return event_type::key_up;
			case SDL_WINDOWEVENT: return event_type::window_event;
			case SDL_MOUSEMOTION: return event_type::mouse_motion;
			case SDL_MOUSEBUTTONDOWN: return event_type::mouse_button_down;
			case SDL_MOUSEBUTTONUP: return event_type::mouse_button_up;
			case SDL_MOUSEWHEEL: return event_type::mouse_wheel;
			default: return event_type::all;
		}
	}
}  // namespace sdlk
