//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <SDL2/SDL.h>
#include <sdlk/game/world.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk
{
    class scene
    {
    protected:
        world m_world;
    public:
        virtual void on_exit() {}
        virtual void on_enter() {}
        virtual void update(const float &dt) {}
        virtual void on_event(const SDL_Event& e) {}
        virtual void render(const std::shared_ptr<gl_program>& program) {}

        virtual ~scene() = default;
    };
}
