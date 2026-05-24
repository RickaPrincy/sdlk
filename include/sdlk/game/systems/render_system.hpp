//
// Created by ricka on 2026-05-24.
//

#pragma once

#include <memory>
#include <sdlk/game/world.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk::game
{
    class render_system
    {
    public:
        static auto update(world &world, const std::shared_ptr<gl_program> &program) -> void;

        render_system() = delete;
    };
}
