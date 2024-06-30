#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include <sdlk/core/component.hpp>
#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/window.hpp>
#include <string>

namespace sdlk
{
	class App
	{
	private:
		EventListener m_event_listener;

	protected:
		const static short FPS_LIMIT = 16;
		Window *p_window = nullptr;
		void limit_fps(unsigned int limit);

	public:
		Window *get_window();
		void run();
		void init_sdl_flags(Uint32 flags);
		void quit_sdl_flags(Uint32 flags);
		void append_child(Component *component);

		App(std::string title, Size size, Uint32 flags = SDL_INIT_EVERYTHING);
		virtual ~App();
	};
}  // namespace sdlk
