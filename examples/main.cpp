#include <sdlk/game/game.hpp>

#include <sdlk/core/gl/gl_texture.hpp>
#include <sdlk/game/components/mesh.hpp>
#include <sdlk/game/components/texture.hpp>
#include <sdlk/game/scenes/game_scene.hpp>
#include <sdlk/core/2d/shape/rectangle_shape.hpp>

using namespace sdlk::game;

static auto opengl_image_entity(world &world) -> void;

auto main(const int argc, char** argv) -> int
{
	game dota("Dota", 1200, 800);

    const auto scene = std::make_shared<game_scene>();
    auto &world = scene->get_world();

    opengl_image_entity(world);

    dota.set_scene(scene);

    return dota.run(argc, argv);
}

auto opengl_image_entity(world &world) -> void
{
    static texture opengl_texture = {
        .m_texture = sdlk::gl_texture::from_file("resources/assets/images/image.png")
    };

    static mesh rectangle_mesh = {
        .m_shape = std::make_shared<sdlk2d::rectangle_shape>(
            glm::vec2{0.0, 0.0},
            316,
            161
        )
    };

    const auto first_object = world.create_entity();
    world.add(first_object, opengl_texture);
    world.add(first_object, rectangle_mesh);
}