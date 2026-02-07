#include <iostream>
#include <sdlk/core/app.hpp>
#include <sdlk/core/components/2d/fonts/msdf_font.hpp>
#include <sdlk/core/components/2d/shape/polygon_shape.hpp>
#include <sdlk/core/components/2d/shape/rectangle_shape.hpp>
#include <sdlk/core/components/2d/shape/text_shape.hpp>
#include <sdlk/core/components/component.hpp>

using namespace sdlk;

auto home() -> std::shared_ptr<renderable>;
auto text_hello_world() -> std::shared_ptr<renderable>;
auto rectangle_with_texture() -> std::shared_ptr<renderable>;
auto rectangle_with_uniform_color() -> std::shared_ptr<renderable>;
auto rectangle_with_vertex_color() -> std::shared_ptr<renderable>;

auto main(const int argc, char** argv) -> int
{
	app rc_engine("RC_Engine", 1200, 800);

	rc_engine.add_view("home", home());

	rc_engine.add_event_listener(
		event_type::key_up, [&](const SDL_Event& event) { std::cout << "Clicked \n"; });

	return rc_engine.run("home", argc, argv);
}

auto home() -> std::shared_ptr<renderable>
{
	auto home = std::make_shared<component>();

	home->add_child(rectangle_with_uniform_color());
	home->add_child(text_hello_world());

	return home;
}

auto text_hello_world() -> std::shared_ptr<renderable>
{
	auto font = msdf_font::make("./resources/assets/fonts/arial.ttf");
	return std::make_shared<sdlk2d::text_shape>(U"Hello World helloé",
		sdlk2d::text_style{ .m_size = 20.0f, .m_fg_color = color::white() },
		font);
}

auto rectangle_with_uniform_color() -> std::shared_ptr<renderable>
{
	return std::make_shared<sdlk2d::rectangle_shape>(
		sdlk2d::type::point{ 0.0f, 0.0f }, 100.0f, 100.0f, color::red());
}

auto rectangle_with_vertex_color() -> std::shared_ptr<renderable>
{
	sdlk2d::type::polygon triangle_with_color = { sdlk2d::type::vertex(
													  { -1.0f, -1.0f }, color::blue()),
		sdlk2d::type::vertex({ 0.0f, 1.0f }, color::red()),
		sdlk2d::type::vertex({ 1.0f, -1.0f }, color::green()) };
	return std::make_shared<sdlk2d::polygon_shape>(triangle_with_color);
}

auto rectangle_with_texture() -> std::shared_ptr<renderable>
{
	const auto texture = gl_texture::from_file("./resources/assets/images/image.png");

	sdlk2d::type::polygon rect_with_uv = { sdlk2d::type::vertex(
											   { 0.5f, 1.0f }, glm::vec2{ 0.0f, 0.0f }),
		sdlk2d::type::vertex({ 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f }),
		sdlk2d::type::vertex({ 1.0f, 0.5f }, glm::vec2{ 1.0f, 1.0f }),

		sdlk2d::type::vertex({ 0.5f, 1.0f }, glm::vec2{ 0.0f, 0.0f }),
		sdlk2d::type::vertex({ 1.0f, 0.5f }, glm::vec2{ 1.0f, 1.0f }),
		sdlk2d::type::vertex({ 0.5f, 0.5f }, glm::vec2{ 0.0f, 1.0f }) };

	return std::make_shared<sdlk2d::polygon_shape>(rect_with_uv, texture);
}