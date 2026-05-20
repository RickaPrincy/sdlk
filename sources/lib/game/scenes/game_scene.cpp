//
// Created by ricka on 2026-05-20.
//

#include <sdlk/game/scenes/game_scene.hpp>

namespace sdlk::game
{
    auto game_scene::update(const float &dt) -> void
    {
        //TODO: input_system, ...
        m_movement_system.update(m_world, dt);
    }

    auto game_scene::on_event(const SDL_Event &e) -> void
    {
        //TODO
    }
}
