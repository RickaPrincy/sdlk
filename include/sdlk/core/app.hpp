#pragma once

#include <SDL2/SDL.h>

#include <sdlk/core/camera.hpp>
#include <sdlk/core/color.hpp>
#include <sdlk/core/components/multiple_view.hpp>
#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/gl/gl_program.hpp>
#include <string>

namespace sdlk
{
    // TODO: Huge refactor... use std::shared_ptr only when needed
	class renderable;
	struct app_options
	{
		bool m_vsync = false;
		unsigned int m_fps{ 30 };
		color m_background{ color::black() };
	};

	class app : public observer
	{
		Uint32 _frame_start{ 0 };
		app_options _options{};
		unsigned int _frame_delay_ms{ 0 };

		std::shared_ptr<class imgui_wrapper> _imgui_wrapper{};

	protected:
		std::shared_ptr<camera> m_camera{};
		std::shared_ptr<gl_program> m_program{};

		SDL_Window *p_window{};
		SDL_GLContext m_opengl_context{ nullptr };

		auto handle_event(SDL_Event &event) const -> void;
		virtual auto limit_fps() -> void;

	    app(const std::string &window_title,
            const int &width,
            const int &height,
            const app_options &options,
            Uint32 sdl_init_flags);
	public:
		std::shared_ptr<multiple_view> m_view{};

	    static auto make(const std::string &window_title,
            const int &width,
            const int &height,
            const app_options &options = {},
            Uint32 sdl_init_flags = SDL_INIT_EVERYTHING) -> std::shared_ptr<app>;

	    static auto get() -> std::shared_ptr<app>;

		auto run(const std::string &default_view, int, char **) -> int;
		auto add_view(const std::string &name, const std::shared_ptr<renderable> &child) const -> void;
	    auto switch_to(const std::string &name, const std::shared_ptr<renderable_context> &context = nullptr) const -> void;

	    app() = delete;
		~app() override;
	};

};	// namespace sdlk
