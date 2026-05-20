//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <sdlk/game/world.hpp>

namespace sdlk
{
    class system
    {
    public:
        virtual auto update(world &world, const float &dt) -> void = 0;

        system() = default;
        virtual ~system() = default;
    };
}