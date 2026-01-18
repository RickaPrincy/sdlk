#include <../include/sdlk/core/components/2d/shape/polygon_shape.hpp>
#include <iostream>
#include <sdlk/core/app.hpp>
#include <sdlk/core/components/2d/rectangle_shape.hpp>
#include <sdlk/core/renderable/component.hpp>

using namespace sdlk;

auto home() -> std::shared_ptr<renderable>;

auto main(const int argc, char** argv) -> int
{
	app rc_engine("RC_Engine", 1200, 800,{
	.background_color = {.r=0, .g=0, .b=0, .a=255}});

	rc_engine.add_view("home", home());

	rc_engine.add_event_listener(event_type::key_down, [](const SDL_Event &event)
	{
		std::cout << "Clicked\n";
	});

	return rc_engine.run(argc, argv);
}

auto home() -> std::shared_ptr<renderable>
{
	const sdlk2d::type::polygon pos{
	    {-1.0f, -1.0f},
		{ 0.0f, 1.0f},
		{ 1.0f,  -1.0f}
	};

	const auto triangle = std::make_shared<sdlk2d::polygon_shape>(pos);

	constexpr sdlk2d::type::point rectangle_origin = {-1.0f, 1.0f};
	const auto rectangle = std::make_shared<sdlk2d::rectangle_shape>(rectangle_origin, 0.5f, 0.5f);

	const auto home = std::make_shared<component>();

	home->add_child(triangle);
	home->add_child(rectangle);

	return home;
}