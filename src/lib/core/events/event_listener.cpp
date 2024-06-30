#include <sdlk/core/events/event_listener.hpp>

void sdlk::EventListener::notify_event(const SDL_Event &event)
{
	const auto event_actions = m_event_listeners.find(event.type);
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
