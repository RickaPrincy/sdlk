#include <sdlk/core/events/observer.hpp>

namespace sdlk
{
	void observer::add_event_listener(event_type event_type,
		event_callback callback,
		bool stop_propagation)
	{
		if (this->m_event_listener)
		{
			this->m_event_listener->m_event_listeners[event_type].push_back(
				{ std::move(callback), stop_propagation });
		}
	}

	observer::observer(std::shared_ptr<event_listener> event_listener)
		: m_event_listener(event_listener)
	{
	}
}  // namespace sdlk
