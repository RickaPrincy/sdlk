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
		virtual ~observer() = default;

		explicit observer(std::shared_ptr<event_listener> event_listener);

		virtual auto add_event_listener(event_type event_type, event_callback callback, bool
			stop_propagation = false) -> void;;

		friend class app;
	};
}  // namespace sdlk
