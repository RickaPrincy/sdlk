#pragma once

#include <memory>
#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/events/types.hpp>

namespace sdlk
{
	class observer
	{
	protected:
		std::shared_ptr<event_listener> m_event_listener = nullptr;

	public:
		observer(std::shared_ptr<event_listener> event_listener);

		virtual void add_event_listener(event_type event_type,
			event_callback callback,
			bool stop_propagation = false);

		friend class app;
	};
}  // namespace sdlk
