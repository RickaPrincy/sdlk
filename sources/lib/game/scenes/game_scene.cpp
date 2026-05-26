//
// Created by ricka on 2026-05-20.
//

#include <sdlk/game/scenes/game_scene.hpp>
#include <sdlk/game/systems/render_system.hpp>
#include <sdlk/game/systems/movement_system.hpp>

namespace sdlk::game
{
    game_scene::game_scene(const glm::vec2 &canva_size) :
        scene(canva_size)
    {
    }

    auto game_scene::update(const float &dt) -> void
    {
        movement_system::update(m_world, dt);
    }

    void game_scene::render(const std::shared_ptr<gl_program> &program)
    {
        render_system::update(m_world, program);
    }
}
