//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <sdlk/game/scenes/scene.hpp>
#include <sdlk/game/systems/movement_system.hpp>

namespace sdlk::game
{
    class game_scene: public scene
    {
        movement_system m_movement_system;
    public:
        game_scene() = default;
        auto update(const float &dt) -> void override;
        auto on_event(const SDL_Event &e) -> void override;
    };
};