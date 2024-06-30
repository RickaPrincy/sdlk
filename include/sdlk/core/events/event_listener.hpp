#pragma once

#include <SDL2/SDL_events.h>

#include <map>
#include <sdlk/core/events/types.hpp>

namespace sdlk
{
	class EventListener
	{
	private:
		std::map<EventType, std::vector<EventAction>> m_event_listeners;

	public:
		virtual ~EventListener() = default;
		EventListener() = default;
		virtual void notify_event(const SDL_Event &event);

		friend class Observer;
	};
}  // namespace sdlk
