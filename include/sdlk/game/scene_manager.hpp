//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <memory>
#include <sdlk/game/scenes/scene.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk::game
{
    class scene_manager
    {
        std::shared_ptr<scene> m_current{};
    public:
        auto update(const float &dt) const -> void;
        auto on_event(const SDL_Event& e) const -> void;
        auto change(const std::shared_ptr<scene> &scene) -> void;
        auto render(const std::shared_ptr<gl_program> &program) const -> void;
    };
}
