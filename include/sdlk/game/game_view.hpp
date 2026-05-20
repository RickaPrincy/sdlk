//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <SDL2/SDL_events.h>
#include <sdlk/game/scene_manager.hpp>
#include <sdlk/core/components/renderable.hpp>
#include <sdlk/core/events/observer.hpp>

namespace sdlk::game
{
    class game_view : public renderable, public observer {
        float m_last_time{0.0f};
        scene_manager m_scene_manager{};

        auto compute_dt() -> float;

    protected:
        virtual auto on_event(const SDL_Event& e) -> void;
        virtual auto on_update(const float &dt) -> void;

        auto render(const std::shared_ptr<gl_program>& program) -> void override;

    public:
	    game_view();
        ~game_view() override = default;
    };
}
