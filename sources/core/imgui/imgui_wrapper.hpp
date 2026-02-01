//
// Created by ricka on 2026-02-01.
//

#pragma once

#include <SDL_video.h>

#include <string>

#include "backends/imgui_impl_sdl2.h"
#include "imgui.h"

namespace sdlk
{

	enum class imgui_theme
	{
		dark,
		light
	};

	struct imgui_wrapper_conf
	{
		imgui_theme m_theme = imgui_theme::dark;
	};

	class imgui_wrapper
	{
		imgui_wrapper_conf m_conf;

	public:
		imgui_wrapper(SDL_Window *window,
			SDL_GLContext *gl_context,
			const std::string &glsl_version,
			const imgui_wrapper_conf &conf = {});

		static auto draw() -> void;
		static auto render() -> void;
		static auto new_frame() -> void;
		static auto process_event(const SDL_Event &event) -> void;

		[[nodiscard]] static auto get_io() -> ImGuiIO &;
		[[nodiscard]] static auto get_dpi() -> float;

		virtual ~imgui_wrapper();
	};
}  // namespace sdlk