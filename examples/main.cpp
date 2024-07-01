#include <sdlk/components/div.hpp>
#include <sdlk/core/window.hpp>
#include <sdlk/sdlk.hpp>

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(500));
	Div square(R_Chess.get_window(), Size(250));

	square.add_event_listener(EventType::KEY_DOWN,
		[](const SDL_Event &event) { printf("Key pressed: %s\n", SDL_GetKeyName(event.key.keysym.sym)); });

	R_Chess.run();
	return 0;
}
