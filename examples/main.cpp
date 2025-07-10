#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

#include <glm/trigonometric.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/types.hpp>

using namespace sdlk;

static const constexpr int WINDOW_WIDTH = 500;
static const constexpr int WINDOW_HEIGHT = 500;

auto main(int argc, char **argv) -> int
{
	app myapp("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT);

	polygon arrow_vertex({ {} });

	polygon_shape arrow(std::move(polygon({
		{ 0, 40 },
		{ 100, 40 },

		{ 100, 0 },
		{ 140, 50 },
		{ 100, 100 },

		{ 100, 60 },
		{ 0, 60 },
	})));

	component component(&myapp, &arrow);

	return myapp.run(argc, argv);
}
