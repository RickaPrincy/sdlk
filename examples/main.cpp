#include <sdlk/components/div.hpp>
#include <sdlk/core/window.hpp>
#include <sdlk/sdlk.hpp>

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(500));
	Div my_div(R_Chess.get_window(), Size(250));

	my_div.add_event_listener(EventType::KEY_DOWN,
		[&](const SDL_Event &event)
		{
			my_div.set_x(my_div.get_x() + 1);
			my_div.active_renderer_childs_state();
		});

	R_Chess.run();
	return 0;
}
