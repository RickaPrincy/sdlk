//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <SDL2/SDL.h>
#include <sdlk/game/world.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk::game
{
    class scene
    {
    protected:
        world m_world{};

    public:
        virtual auto on_exit() -> void {}
        virtual auto on_enter() -> void {}
        virtual auto on_event(const SDL_Event& e) ->void {}

        virtual auto update(const float &dt) -> void {}
        virtual auto render(const std::shared_ptr<gl_program>& program) -> void {}

        [[nodiscard]] auto get_world() -> world&
        {
            return m_world;
        }

        virtual ~scene() = default;
    };
}
