//
// Created by ricka on 2026-05-20.
//

// ReSharper disable CppUseStructuredBinding
#include <sdlk/game/systems/movement_system.hpp>

namespace sdlk::game
{
    auto movement_system::update(world &world, const float &dt) -> void
    {
        auto &transforms = world.pool<transform>();
        auto &velocities = world.pool<velocity>();

        for (const auto entity : velocities.get_entities())
        {
            if (!transforms.has(entity))
            {
                continue;
            }

            auto& t = transforms.get(entity);
            auto& v = velocities.get(entity);
            t.add_translation(v.m_v * dt);
        }
    }
}