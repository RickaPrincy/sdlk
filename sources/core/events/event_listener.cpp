#include <SDL2/SDL_events.h>

#include <sdlk/core/events/event_listener.hpp>

void sdlk::event_listener::notify_event(const SDL_Event &event)
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

auto sdlk::event_listener::get_event_type_value(const SDL_Event &event) -> sdlk::event_type
{
	switch (event.type)
	{
		case SDL_KEYDOWN: return sdlk::event_type::key_down;
		case SDL_KEYUP: return sdlk::event_type::key_up;
		case SDL_WINDOWEVENT: return sdlk::event_type::window_event;
		case SDL_MOUSEMOTION: return sdlk::event_type::mouse_motion;
		case SDL_MOUSEBUTTONDOWN: return sdlk::event_type::mouse_button_down;
		case SDL_MOUSEBUTTONUP: return sdlk::event_type::mouse_button_up;
		case SDL_MOUSEWHEEL: return sdlk::event_type::mouse_wheel;
		default: return sdlk::event_type::all;
	}
}
