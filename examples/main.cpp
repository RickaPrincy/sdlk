#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

#include <glm/trigonometric.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/types.hpp>

using namespace sdlk;

static const constexpr int WINDOW_WIDTH = 700;
static const constexpr int WINDOW_HEIGHT = 700;

auto main(int argc, char **argv) -> int
{
	app myapp("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT);

	colored_shape arrow_shape(std::move(polygon({
								  { 0, 40 },
								  { 100, 40 },

								  { 100, 0 },
								  { 140, 50 },
								  { 100, 100 },

								  { 100, 60 },
								  { 0, 60 },
							  })),
		{ 200, 30, 78, 255 });
	component arrow_component(&myapp, &arrow_shape);

	arrow_component.translate({ 50, 200 });

	image_shape image("./assets/images/image.png", 287, 90);
	component image_component(&myapp, &image);

	return myapp.run(argc, argv);
}
