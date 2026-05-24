//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <memory>
#include <sdlk/game/scenes/scene.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk::game
{
    class game_scene: public scene
    {
    public:
        game_scene() = default;

        auto update(const float &dt) -> void override;
        auto render(const std::shared_ptr<gl_program> &program) -> void override;
    };
};