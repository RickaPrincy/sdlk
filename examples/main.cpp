#include <sdlk/components/square.hpp>
#include <sdlk/core/window.hpp>
#include <sdlk/sdlk.hpp>

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(500));
	Square square(R_Chess.get_window(), Size(250));

	square.add_event_listener(
		SDL_KEYDOWN, [](const SDL_Event &event) { printf("Key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym)); });

	R_Chess.run();
	return 0;
}
