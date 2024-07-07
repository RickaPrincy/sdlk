#include <iostream>
#include <sdlk/components/image.hpp>
#include <sdlk/components/text.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/sdlk.hpp>

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(700, 550));
	Image my_image(R_Chess.get_window(),
		// we can use relative path here
		"/home/ricka/Ricka/project/2024/sdlk/examples/assets/images/image.png",
		Size(500, 150),
		Position(60, 0));
	R_Chess.run();
	return 0;
}
