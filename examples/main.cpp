#include <sdlk/components/div.hpp>
#include <sdlk/components/image.hpp>
#include <sdlk/sdlk.hpp>

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(700));
	Div my_div(R_Chess.get_window(), Size(50));
	Image my_image(R_Chess.get_window(),
		"/home/ricka/Ricka/project/2024/sdlk/examples/assets/image.png",
		Size(500, 150),
		Position(60, 0));

	my_div.add_event_listener(EventType::KEY_DOWN,
		[&](const SDL_Event &event)
		{
			my_div.set_x(my_div.get_x() + 1);
			my_div.active_renderer_childs_state();
		});

	R_Chess.run();
	return 0;
}
