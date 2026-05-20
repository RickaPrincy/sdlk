//
// Created by ricka on 2026-05-20.
//

#include <sdlk/game/game_view.hpp>
#include <SDL2/SDL.h>

namespace sdlk
{
    game_view::game_view()
    {
        this->observer::add_event_listener(
            event_type::all,
            [&](const SDL_Event& e) {
            on_event(e) ;
        });
    }

    auto game_view::compute_dt() -> float
    {
        const float now = static_cast<float>(SDL_GetTicks()) / 1000.0f;
        const float dt = now - m_last_time;
        m_last_time = now;
        return dt;
    }

    auto game_view::on_event(const SDL_Event &e) -> void
    {
        m_scene_manager.on_event(e);
    }

    auto game_view::on_update(const float &dt) -> void
    {
        m_scene_manager.update(dt);
    }

    auto game_view::render(const std::shared_ptr<gl_program> &program) -> void
    {
        const auto dt = compute_dt();

        on_update(dt);

        m_scene_manager.render(program);
    }
}
