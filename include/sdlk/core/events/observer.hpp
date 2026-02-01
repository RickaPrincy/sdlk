#pragma once

#include <sdlk/core/events/types.hpp>

namespace sdlk
{
	class observer
	{
	public:
		virtual ~observer() = default;
		explicit observer() = default;

		virtual auto add_event_listener(event_type event_type,
			event_callback callback,
			bool stop_propagation = false) -> void;

		friend class app;
	};
}  // namespace sdlk
