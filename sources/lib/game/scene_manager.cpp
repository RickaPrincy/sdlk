//
// Created by ricka on 2026-05-20.
//

#include <sdlk/game/scene_manager.hpp>

namespace sdlk::game
{
    auto scene_manager::change(std::unique_ptr<scene> scene) -> void
    {
        if (m_current)
        {
            m_current->on_exit();
        }

        m_current = std::move(scene);

        if (m_current)
        {
            m_current->on_enter();
        }
    }

    auto scene_manager::on_event(const SDL_Event &e) const -> void
    {
        if (m_current)
        {
            m_current->on_event(e);
        }
    }

    auto scene_manager::update(const float &dt) const -> void {
        if (m_current)
        {
            m_current->update(dt);
        }
    }

    auto scene_manager::render(const std::shared_ptr<gl_program>& program) const -> void
    {
        if (m_current)
        {
            m_current->render(program);
        }
    }
}
