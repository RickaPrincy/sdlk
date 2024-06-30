#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/window.hpp>
#include <string>
#include <vector>

#include "sdlk/core/component.hpp"

namespace sdlk
{
	class App
	{
	private:
		std::vector<Observer *> m_observers{};
		void add_observer(Observer *observer);
		void notify_observers(const SDL_Event &event);

	protected:
		const static short FPS_LIMIT = 16;
		Window *p_window = nullptr;
		void limit_fps(unsigned int limit);

	public:
		CP_GETTER(Window, window)
		void run();
		void init_sdl_flags(Uint32 flags);
		void quit_sdl_flags(Uint32 flags);
		void append_child(Component *component);

		App(std::string title, Size size, Uint32 flags = SDL_INIT_EVERYTHING);
		virtual ~App();
	};
}  // namespace sdlk
