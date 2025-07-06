#include <SDL2/SDL_ttf.h>

#include <sdlk/core/app.hpp>
#include <sdlk/core/types.hpp>

using namespace sdlk;

auto main(int argc, char **argv) -> int
{
	app myapp("Hello World", 500, 500);

	polygon arrow_vertex({ {
		// Shaft rectangle (starting from origin)
		{ 0, 40 },	// bottom-left
		{ 100, 40 },

		{ 100, 0 },
		{ 140, 50 },
		{ 100, 100 },

		{ 100, 60 },
		{ 0, 60 },
	} });

	component arrow(myapp, std::move(arrow_vertex));

	return myapp.run(argc, argv);
}
