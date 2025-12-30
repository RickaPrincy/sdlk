#include <iostream>
#include <sdlk/core/app.hpp>

using namespace sdlk;

auto main(const int argc, char** argv) -> int
{
	app rc_engine("RC_Engine", 1200, 800);

	rc_engine.add_event_listener(event_type::key_down, [&](const SDL_Event &event)
	{
		std::cout << "clicked\n";
	});

	return rc_engine.run(argc, argv);
}