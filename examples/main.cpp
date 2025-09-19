#include <SDL2/SDL_events.h>

#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/core/quad.hpp>
#include <sdlk/core/fonts/msdf_font.hpp>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/types.hpp>

using namespace sdlk;

static constexpr int WINDOW_WIDTH = 1000;
static constexpr int WINDOW_HEIGHT = 1000;

auto main(int argc, char** argv) -> int
{
	app myapp("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT);

	auto font = msdf_font::make("./resources/assets/font/arial.ttf");
	text_shape hello_world("hello world", font, { .r=255, .g=0, .b=0, .a=255 });
	myapp.add_renderable(&hello_world);

	return myapp.run(argc, argv);
}
