//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <sdlk/game/systems/system.hpp>

namespace sdlk::game
{
    class movement_system: public system
    {
    public:
        auto update(world &world, const float &dt) -> void override;

        movement_system() = default;
    };
}
