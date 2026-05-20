//
// Created by ricka on 2026-05-20.
//


#include <cassert>
#include <sdlk/game/entity_manager.hpp>

namespace sdlk::game
{
    auto entity_manager::create() -> entity
    {
        uint32_t id;

        if (!m_free.empty())
        {
            id = m_free.back();
            m_free.pop_back();
        }
        else
        {
            id = m_next++;
            m_generation.push_back(0);
        }

        return entity{.m_id=id, .m_generation=m_generation[id]};
    }

    auto entity_manager::destroy(const entity e) -> void
    {
        assert(valid(e));
        m_generation[e.m_id]++;
        m_free.push_back(e.m_id);
    }

    auto entity_manager::valid(const entity e) const -> bool
    {
        return e.m_id < m_generation.size() &&m_generation[e.m_id] == e.m_generation;
    }
}
