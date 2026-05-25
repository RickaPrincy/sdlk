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
        glm::vec2 m_canva_size{};

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

        [[nodiscard]] auto get_canva_size() const -> glm::vec2
        {
            return m_canva_size;
        }

        explicit scene(const glm::vec2 &canva_size)
            :m_canva_size(canva_size)
        {}

        virtual ~scene() = default;
    };
}
