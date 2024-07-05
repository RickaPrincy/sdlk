#include <sdlk/core/events/observer.hpp>
#include <sdlk/utils/basic_wrapper.hpp>

void sdlk::Observer::add_event_listener(sdlk::EventType event_type, sdlk::EventCallback callback, bool stop_propagation)
{
	if (!sdlk::check::is_null(p_event_listener))
	{
		p_event_listener->m_event_listeners[event_type].push_back({ callback, stop_propagation });
	}
}
