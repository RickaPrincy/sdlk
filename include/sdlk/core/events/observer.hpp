#pragma once

#include <SDL2/SDL_events.h>

namespace sdlk
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void on_event(const SDL_Event &event) = 0;
	};
}  // namespace sdlk
