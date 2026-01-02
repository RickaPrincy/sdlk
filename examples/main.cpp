#include <sdlk/core/app.hpp>

#include <sdlk/core/renderable/colored_shape.hpp>
#include <sdlk/core/renderable/component.hpp>
#include <sdlk/core/renderable/type.hpp>

using namespace sdlk;

auto home() -> std::shared_ptr<renderable>;

auto main(const int argc, char** argv) -> int
{
	app rc_engine("RC_Engine", 1200, 800,{
	.background_color = {.r=0, .g=0, .b=0, .a=255}});

	rc_engine.add_view("home", home());
	return rc_engine.run(argc, argv);
}

auto home() -> std::shared_ptr<renderable>
{
	const type::polygon pos{
	    {-1.0f, -1.0f, 0.0f},
		{ 0.0f, 1.0f, 0.0f},
		{ 1.0f,  -1.0f, 0.0f}
	};
	constexpr SDL_Color color{ .r = 255, .g = 0, .b = 155, .a = 255 };

	const auto triangle = std::make_shared<colored_shape>(pos, color);
	const auto home = std::make_shared<component>();
	home->add_child(triangle);

	return home;
}