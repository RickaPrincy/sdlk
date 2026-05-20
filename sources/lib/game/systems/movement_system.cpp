//
// Created by ricka on 2026-05-20.
//

// ReSharper disable CppUseStructuredBinding
#include <sdlk/game/systems/movement_system.hpp>

namespace sdlk
{
    auto movement_system::update(world &world, const float &dt) -> void
    {
        auto &transforms = world.pool<transform>();
        auto &velocities = world.pool<velocity>();

        for (const auto entity : transforms.get_entities())
        {
            if (!velocities.has(entity))
            {
                continue;
            }

            auto& t = transforms.get(entity);
            const auto& v = velocities.get(entity);

            t.m_x += v.m_x * dt;
            t.m_y += v.m_y * dt;
        }
    }
}