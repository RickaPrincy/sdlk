#include <SDL2/SDL_events.h>

#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/core/freetype_font.hpp>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/types.hpp>

using namespace sdlk;

static constexpr int WINDOW_WIDTH = 1000;
static constexpr int WINDOW_HEIGHT = 1000;

auto main(int argc, char** argv) -> int
{
	app myapp("Hello World", WINDOW_WIDTH, WINDOW_HEIGHT);

	auto image = texture::from_file("./resources/assets/images/image.png");
	textured_shape shape(
		std::move(polygon(quad::make(image->get_width() / 2, image->get_height() / 2))),
		quad::make(image->get_width() / 2, image->get_height() / 2),
		image);

	textured_shape shape2(
		std::move(polygon(quad::make(image->get_width() / 2, image->get_height() / 2))),
		quad::make(image->get_width() / 2, image->get_height() / 2),
		image);

	shape2.translate({ 40.f, 50.f });

	colored_shape test(polygon({
						   { 0, 0 },
						   { 50, 0 },
						   { 50, 50 },
						   { 0, 50 },
					   }),
		{ 255, 0, 0, 255 },
		true);

	auto font = freetype_font::make("./resources/assets/font/arial.ttf");

	text_shape blibli("hello world", font, { 255, 0, 0, 255 });

	myapp.add_renderable(&shape);
	myapp.add_renderable(&shape2);
	myapp.add_renderable(&test);
	myapp.add_renderable(&blibli);

	myapp.add_event_listener(
		event_type::key_down, [&](const SDL_Event& event) { shape.translate({ 50, 50 }); });

	myapp.add_event_listener(event_type::mouse_button_down,
		[&](const SDL_Event& event) { shape.translate({ 100, 100 }); });

	myapp.add_event_listener(
		event_type::mouse_button_up, [&](const SDL_Event&) { shape.scale(1.1f); });

	return myapp.run(argc, argv);
}
