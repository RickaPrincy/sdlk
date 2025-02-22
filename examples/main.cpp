#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <sdlk/components/image.hpp>
#include <sdlk/components/text.hpp>
#include <sdlk/core/app.hpp>

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(700, 550));
	Image my_image(
		R_Chess.get_window(), "./assets/images/image.png", Size(500, 150), Position(60, 0));
	auto arial = TTF_OpenFont("./assets/font/arial.ttf", 25);
	Text my_text(&my_image, "Hello world", { 0, 255, 255 }, arial);

	my_text.add_event_listener(sdlk::EventType::KEY_DOWN,
		[&](const SDL_Event &event)
		{
			my_text.set_x(event.motion.x);
			my_text.set_y(event.motion.y);
			my_text.do_re_render();
			std::cout << "Helo" << std::endl;
		});

	R_Chess.run();
	return 0;
}
