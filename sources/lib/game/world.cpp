//
// Created by ricka on 2026-05-20.
//

#include <sdlk/game/world.hpp>

#include "../../../include/sdlk/game/component_pool.hpp"
#include "entity_manager.hpp"

namespace sdlk
{
    auto world::create_entity() const -> entity
    {
        return m_entity_manager->create();
    }

    auto world::destroy_entity(const entity entity) const -> void
    {
        m_transforms->remove(entity);
        m_velocities->remove(entity);
        m_entity_manager->destroy(entity);
    }
}
