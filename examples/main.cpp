#include <SDL2/SDL_ttf.h>

#include <sdlk/core/app.hpp>

using namespace sdlk;

auto main(int argc, char **argv) -> int
{
	app myapp("Hello World", { 400, 500 });

	return myapp.run(argc, argv);
}
