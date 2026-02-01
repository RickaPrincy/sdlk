#pragma once

#include <SDL2/SDL_events.h>

#include <map>
#include <memory>
#include <sdlk/core/events/types.hpp>

namespace sdlk
{
	class event_listener
	{
	protected:
		std::map<event_type, std::vector<event_action>> m_event_listeners{};

	public:
		event_listener() = default;

		virtual ~event_listener() = default;

		virtual void notify_event(const SDL_Event &event);

		static auto get_event_type_value(const SDL_Event &event) -> event_type;

		[[nodiscard]] static auto instance() -> std::shared_ptr<event_listener>;

		friend class observer;
	};
}  // namespace sdlk
