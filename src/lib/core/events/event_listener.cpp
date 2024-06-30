#include <SDL2/SDL_events.h>

#include <sdlk/core/events/event_listener.hpp>

void sdlk::EventListener::notify_event(const SDL_Event &event)
{
	const auto event_actions = m_event_listeners.find(sdlk::EventListener::get_event_type_value(event));
	if (event_actions == m_event_listeners.end())
	{
		return;
	}

	for (const auto action : event_actions->second)
	{
		action.m_callback(event);
		if (action.m_stop_propagation)
		{
			break;
		}
	};
}

sdlk::EventType sdlk::EventListener::get_event_type_value(const SDL_Event &event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN: return sdlk::EventType::KEY_DOWN;
		case SDL_KEYUP: return sdlk::EventType::KEY_UP;
		case SDL_WINDOWEVENT: return sdlk::EventType::WINDOW_EVENT;
		case SDL_MOUSEMOTION: return sdlk::EventType::MOUSE_MOTION;
		case SDL_MOUSEBUTTONDOWN: return sdlk::EventType::MOUSE_BUTTON_DOWN;
		case SDL_MOUSEBUTTONUP: return sdlk::EventType::MOUSE_BUTTON_UP;
		case SDL_MOUSEWHEEL: return sdlk::EventType::MOUSE_WHEEL;
		default: return sdlk::EventType::NOT_SUPPORTED;
	}
}
