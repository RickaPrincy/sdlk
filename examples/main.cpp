#include <sdlk/core/app.hpp>
#include <sdlk/core/components/2d/shape/polygon_shape.hpp>
#include <sdlk/core/components/2d/shape/rectangle_shape.hpp>
#include <sdlk/core/fonts/msdf_font.hpp>
#include <sdlk/core/renderable/component.hpp>
#include <sdlk/core/components/2d/shape/text_shape.hpp>

using namespace sdlk;

auto home() -> std::shared_ptr<renderable>;
auto text_hello_world() -> std::shared_ptr<renderable>;
auto rectangle_with_texture() -> std::shared_ptr<renderable>;
auto rectangle_with_uniform_color() -> std::shared_ptr<renderable>;
auto rectangle_with_vertex_color() -> std::shared_ptr<renderable>;

auto main(const int argc, char** argv) -> int
{
	app rc_engine(
		"RC_Engine", 1200, 800, { .background_color = { .r = 0, .g = 0, .b = 0, .a = 255 } });

	rc_engine.add_view("home", home());

	return rc_engine.run(argc, argv);
}

auto home() -> std::shared_ptr<renderable>
{
	auto home = std::make_shared<component>();

	home->add_child(text_hello_world());

	return home;
}

auto text_hello_world() -> std::shared_ptr<renderable>
{
	auto font = msdf_font::make("./resources/assets/fonts/arial.ttf");
	return std::make_shared<sdlk2d::text_shape>("Hello World!", font);
}

auto rectangle_with_uniform_color() -> std::shared_ptr<renderable>
{
	return std::make_shared<sdlk2d::rectangle_shape>(sdlk2d::type::point{ -1.0f, 1.0f },
		0.5f,
		0.5f,
		SDL_Color{ .r = 0, .g = 0, .b = 255, .a = 255 });
}

auto rectangle_with_vertex_color() -> std::shared_ptr<renderable>
{
	sdlk2d::type::polygon triangle_with_color = { sdlk2d::type::vertex({ -1.0f, -1.0f },
													  SDL_Color{ 255, 0, 0, 255 }),
		sdlk2d::type::vertex({ 0.0f, 1.0f }, SDL_Color{ 0, 255, 0, 255 }),
		sdlk2d::type::vertex({ 1.0f, -1.0f }, SDL_Color{ 0, 0, 255, 255 }) };
	return std::make_shared<sdlk2d::polygon_shape>(triangle_with_color);
}

auto rectangle_with_texture() -> std::shared_ptr<renderable>
{
	const auto texture = sdlk2d::texture::from_file("./resources/assets/images/image.png");

	sdlk2d::type::polygon rect_with_uv = { sdlk2d::type::vertex(
											   { 0.5f, 1.0f }, glm::vec2{ 0.0f, 0.0f }),
		sdlk2d::type::vertex({ 1.0f, 1.0f }, glm::vec2{ 1.0f, 0.0f }),
		sdlk2d::type::vertex({ 1.0f, 0.5f }, glm::vec2{ 1.0f, 1.0f }),

		sdlk2d::type::vertex({ 0.5f, 1.0f }, glm::vec2{ 0.0f, 0.0f }),
		sdlk2d::type::vertex({ 1.0f, 0.5f }, glm::vec2{ 1.0f, 1.0f }),
		sdlk2d::type::vertex({ 0.5f, 0.5f }, glm::vec2{ 0.0f, 1.0f }) };

	return std::make_shared<sdlk2d::polygon_shape>(rect_with_uv, texture);
}