//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <sdlk/game/world.hpp>

namespace sdlk::game
{
    class movement_system
    {
    public:
        static auto update(world &world, const float &dt) -> void;

        movement_system() = delete;
    };
}
