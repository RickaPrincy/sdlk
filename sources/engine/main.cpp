//
// Created by ricka on 2026-02-01.
//

#include <sdlk/core/app.hpp>

auto main(int argc, char *argv[]) -> int
{
	sdlk::app sdlk_engine("Sdlk Engine", 1280, 720);

	return sdlk_engine.run(argc, argv);
}
