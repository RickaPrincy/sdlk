#include <sdlk/core/events/observer.hpp>
#include <sdlk/utils/basic_wrapper.hpp>

void sdlk::observer::add_event_listener(sdlk::event_type event_type,
	sdlk::event_callback callback,
	bool stop_propagation)
{
	if (!p_event_listener)
	{
		p_event_listener->m_event_listeners[event_type].push_back(
			{ std::move(callback), stop_propagation });
	}
}
