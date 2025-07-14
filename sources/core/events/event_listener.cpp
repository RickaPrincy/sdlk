#include <SDL2/SDL_events.h>

#include <sdlk/core/events/event_listener.hpp>

void sdlk::event_listener::notify_event(const SDL_Event &event)
{
	const auto event_actions =
		m_event_listeners.find(sdlk::event_listener::get_event_type_value(event));
	if (event_actions == m_event_listeners.end())
	{
		return;
	}

	for (const auto &action : event_actions->second)
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
		case SDL_KEYDOWN: return sdlk::event_type::KEY_DOWN;
		case SDL_KEYUP: return sdlk::event_type::KEY_UP;
		case SDL_WINDOWEVENT: return sdlk::event_type::WINDOW_EVENT;
		case SDL_MOUSEMOTION: return sdlk::event_type::MOUSE_MOTION;
		case SDL_MOUSEBUTTONDOWN: return sdlk::event_type::MOUSE_BUTTON_DOWN;
		case SDL_MOUSEBUTTONUP: return sdlk::event_type::MOUSE_BUTTON_UP;
		case SDL_MOUSEWHEEL: return sdlk::event_type::MOUSE_WHEEL;
		default: return sdlk::event_type::NOT_SUPPORTED;
	}
}
