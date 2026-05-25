//
// Created by ricka on 2026-02-01.
//

#include <sdlk/core/app.hpp>
#include "views/view.hpp"
#include "theme.hpp"

using namespace sdlk::engine;

auto main(const int argc, char* argv[]) -> int
{
	sdlk::app sdlk_engine("Sdlk Engine", 1280, 720);

	configure_theme();

	sdlk_engine.add_view("home", home());
	sdlk_engine.add_view("project_editor", project_editor());
	return sdlk_engine.run("home", argc, argv);
}