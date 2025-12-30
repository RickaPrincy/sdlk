#pragma once

#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/gl_program.hpp>
#include <sdlk/core/multiple_view.hpp>

#include  <SDL2/SDL.h>
#include <string>

namespace sdlk
{
	class renderable;
	struct app_options
	{
		unsigned int fps{30};
		SDL_Color background_color{ .r=0, .g=0, .b=0, .a=255 };
	};

	class app : public observer
	{
		Uint32 _frame_start{0};
		app_options _options{};
		unsigned int _frame_delay_ms{0};

		static unsigned int _s_window_width, _s_window_height;

	protected:
		std::shared_ptr<multiple_view> m_view{};
		std::shared_ptr<gl_program> m_program{};

		SDL_Window *p_window{};
		SDL_GLContext m_opengl_context{nullptr};

	public:
		app(const std::string &window_title,
			const int &width,
			const int &height,
			const app_options &options = {},
			Uint32 sdl_init_flags = SDL_INIT_EVERYTHING);

		virtual auto limit_fps() -> void;

		auto run(int argc, char **argv) -> int;
		auto add_view(const std::string &name, const std::shared_ptr<multiple_view> &child) const
			-> void;

		[[nodiscard]] static auto get_width() -> unsigned int;
		[[nodiscard]] static auto get_height() -> unsigned int;

		[[nodiscard]] auto get_event_listener() -> std::shared_ptr<event_listener>;

		~app() override;
	};

};	// namespace sdlk
