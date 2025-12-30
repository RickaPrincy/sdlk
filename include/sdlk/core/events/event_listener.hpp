#pragma once

#include <SDL2/SDL_events.h>

#include <map>
#include <sdlk/core/events/types.hpp>

namespace sdlk
{
	class event_listener
	{
		std::map<event_type, std::vector<event_action>> m_event_listeners;

	public:
		virtual ~event_listener() = default;

		event_listener() = default;

		virtual void notify_event(const SDL_Event &event);

		static auto get_event_type_value(const SDL_Event &event) -> event_type;

		friend class observer;
	};
}  // namespace sdlk
