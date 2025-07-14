#include <SDL2/SDL_events.h>
#include <filesystem>
#include <glm/trigonometric.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/core/freetype_font.hpp>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/types.hpp>

using namespace sdlk;

static const constexpr int WINDOW_WIDTH = 1000;
static const constexpr int WINDOW_HEIGHT = 1000;

auto main(int argc, char** argv) -> int
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

	myapp.add_event_listener(event_type::MOUSE_WHEEL,
		[&](const SDL_Event& event)
		{
			auto* cam = myapp.get_camera();

			// Étape 1 : position souris en pixels
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			glm::vec2 mouse_screen = { static_cast<float>(mx), static_cast<float>(my) };

			// Étape 2 : position dans le monde avant zoom
			glm::vec2 world_before = mouse_screen / cam->get_zoom();

			// Étape 3 : modifier le zoom (exponentiel pour plus fluide)
			float zoom = cam->get_zoom();
			float zoom_step = 1.1f;
			if (event.wheel.y > 0)
				zoom *= zoom_step;	// scroll up = zoom in
			else if (event.wheel.y < 0)
				zoom /= zoom_step;	// scroll down = zoom out

			cam->set_zoom(zoom);

			// Étape 4 : position dans le monde après zoom
			glm::vec2 world_after = mouse_screen / cam->get_zoom();

			// Étape 5 : ajuster position pour que la souris "reste sur le même point"
			glm::vec2 delta = world_before - world_after;
			cam->set_position(cam->get_position() + delta / cam->get_zoom());
		});

	myapp.add_event_listener(event_type::MOUSE_MOTION,
		[&](const SDL_Event& event)
		{
			float mouse_x = static_cast<float>(event.motion.x);
			float mouse_y = static_cast<float>(event.motion.y);

			auto cam = myapp.get_camera();

			glm::vec2 zoomed_size = { static_cast<float>(app::get_width()),
				static_cast<float>(app::get_height()) };

			glm::vec2 world_mouse = glm::vec2(mouse_x, mouse_y) / cam->get_zoom();

			glm::vec2 centered_camera_pos = world_mouse - (zoomed_size / cam->get_zoom()) * 0.5f;

			cam->set_position(centered_camera_pos);
		});

	image_shape image("./assets/images/image.png", 287, 90);
	component image_component(&myapp, &image);

	image_component.translate({ 500, 0 });

	auto font =
		freetype_font::make(std::filesystem::absolute("assets/font/arial.ttf").string(), 20);

	text_shape text("hello", font, { 255, 255, 0, 255 });
	component text_component(&myapp, &text);

	myapp.add_event_listener(
		event_type::KEY_DOWN, [&](const SDL_Event& event) { text_component.translate({ 20, 0 }); });

	return myapp.run(argc, argv);
}
