#pragma once

#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/events/types.hpp>

namespace sdlk
{
	class observer
	{
	protected:
		event_listener *p_event_listener = nullptr;

	public:
		observer() = default;
		virtual void add_event_listener(event_type event_type,
			event_callback callback,
			bool stop_propagation = false);

		friend class App;
	};
}  // namespace sdlk
