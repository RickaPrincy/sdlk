#include <SDL2/SDL_ttf.h>

#include <sdlk/core/app.hpp>

using namespace sdlk;

auto main(int argc, char **argv) -> int
{
	app myapp("Hello World", { 500, 500 });

	component first_child({ { 0, 0}, { 0, 500}, { 250, 250} }, { 500, 500 });

	myapp.append_child(&first_child);

	return myapp.run(argc, argv);
}
