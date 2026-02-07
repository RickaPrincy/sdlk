//
// Created by ricka on 2026-02-01.
//

#include <sdlk/core/app.hpp>

#include "imgui.h"
#include "views/view.hpp"

using namespace sdlk;

static auto configure_global_style() -> void;

auto main(const int argc, char* argv[]) -> int
{
	app sdlk_engine("Sdlk Engine", 1280, 720);

	configure_global_style();

	sdlk_engine.add_view("home", home());
	return sdlk_engine.run("home", argc, argv);
}

static auto configure_global_style() -> void
{
	auto& style = ImGui::GetStyle();

	// scrollbar
	style.GrabRounding = 8.0f;
	style.ScrollbarSize = 10.0f;
	style.ScrollbarRounding = 8.0f;

	// window
	style.WindowRounding = 8.0f;
	style.WindowPadding = ImVec2(10, 10);

	// button
	style.FrameRounding = 8.0f;
	style.FramePadding = ImVec2(10, 10);
}
