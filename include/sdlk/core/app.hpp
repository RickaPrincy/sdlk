#pragma once

#include <SDL2/SDL_pixels.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>

#include <glm/glm.hpp>
#include <sdlk/core/camera.hpp>
#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/renderable.hpp>
#include <string>
#include <vector>

namespace sdlk
{
	struct app_options
	{
		unsigned int fps = 30;
		std::string vertex_source = "";
		std::string fragment_source = "";
		SDL_Color background_color = { 0, 0, 0, 255 };
	};

	class app : public observer
	{
	private:
		app_options _options{};
		Uint32 _frame_start = 0;
		unsigned int _frame_delay_ms = 0;

		static FT_Library s_ft_library;
		static unsigned int s_window_width, s_window_height;

	protected:
		camera m_camera;
		GLuint m_shader_program{};

		SDL_Window *p_window = nullptr;
		std::vector<renderable *> m_childs{};
		SDL_GLContext m_opengl_context = nullptr;

	public:
		app(std::string window_title,
			int width,
			int height,
			app_options options = {},
			Uint32 sdl_init_flags = SDL_INIT_EVERYTHING);

		virtual auto limit_fps() -> void;
		auto run(int argc, char **argv) -> int;
		auto add_renderable(renderable *child) -> void;

		[[nodiscard]] auto get_camera() -> camera *;

		[[nodiscard]] static auto get_width() -> int const;
		[[nodiscard]] static auto get_height() -> int const;
		[[nodiscard]] static auto get_ft_library() -> FT_Library &;
		[[nodiscard]] auto get_event_listener() -> std::shared_ptr<event_listener> const;

		virtual ~app();
	};

};	// namespace sdlk
