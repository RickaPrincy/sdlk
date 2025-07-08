#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

#include <sdlk/core/app.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/core/types.hpp>

using namespace sdlk;

static const constexpr int WINDOW_WIDTH = 500;
static const constexpr int WINDOW_HEIGHT = 500;

auto main(int argc, char **argv) -> int
{
	app myapp("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT);

	polygon arrow_vertex({ {
		{ 0, 40 },
		{ 100, 40 },

		{ 100, 0 },
		{ 140, 50 },
		{ 100, 100 },

		{ 100, 60 },
		{ 0, 60 },
	} });

	shape arrow(std::move(arrow_vertex), myapp.get_width(), myapp.get_height());
	component arrow_component(&myapp, &arrow);

	arrow_component.add_event_listener(event_type::MOUSE_BUTTON_DOWN,
		[&](const SDL_Event &event) { arrow_component.translate({ 10.0, 0.0 }); });

	return myapp.run(argc, argv);
}
