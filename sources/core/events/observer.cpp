#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/events/observer.hpp>
#include <utility>

namespace sdlk
{
	auto observer::add_event_listener(const event_type event_type,
		event_callback callback,
		const bool stop_propagation) -> void
	{
		event_listener::instance()->m_event_listeners[event_type].push_back(
			{ std::move(callback), stop_propagation });
	}
}  // namespace sdlk
