#pragma once

#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/events/types.hpp>

namespace sdlk
{
	class Observer
	{
	protected:
		EventListener *p_event_listener = nullptr;

	public:
		Observer() = default;
		void add_event_listener(EventType event_type, EventCallback callback, bool stop_propagation = false);

		friend class App;
	};
}  // namespace sdlk
