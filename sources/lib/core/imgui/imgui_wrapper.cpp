//
// Created by ricka on 2026-02-01.
//

#include "imgui_wrapper.hpp"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "imgui.h"

namespace sdlk
{
	imgui_wrapper::imgui_wrapper(SDL_Window *window,
		SDL_GLContext *gl_context,
		const std::string &glsl_version,
		const imgui_wrapper_conf &conf)
		: m_conf(conf)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		if (m_conf.m_theme == imgui_theme::dark)
		{
			ImGui::StyleColorsDark();
		}
		else
		{
			ImGui::StyleColorsLight();
		}

		auto &io = get_io();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		const auto dpi = get_dpi();
		auto &style = ImGui::GetStyle();
		style.ScaleAllSizes(dpi);
		style.FontScaleDpi = dpi;

		ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
		ImGui_ImplOpenGL3_Init(glsl_version.c_str());
	}

	auto imgui_wrapper::process_event(const SDL_Event &event) -> void
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}

	auto imgui_wrapper::draw() -> void
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	auto imgui_wrapper::render() -> void
	{
		ImGui::Render();
	}

	auto imgui_wrapper::new_frame() -> void
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}

	auto imgui_wrapper::get_io() -> ImGuiIO &
	{
		return ImGui::GetIO();
	}

	auto imgui_wrapper::get_dpi() -> float
	{
		return ImGui_ImplSDL2_GetContentScaleForDisplay(0);
	}

	imgui_wrapper::~imgui_wrapper()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}
}  // namespace sdlk
