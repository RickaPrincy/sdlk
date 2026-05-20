//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <memory>
#include <sdlk/game/entity.hpp>
#include <sdlk/game/component_pool.hpp>
#include <sdlk/game/components/transform.hpp>
#include <sdlk/game/components/velocity.hpp>

namespace sdlk
{
    class entity_manager;

    class world
    {
        std::shared_ptr<entity_manager> m_entity_manager{};
        std::shared_ptr<component_pool<velocity>> m_velocities{};
        std::shared_ptr<component_pool<transform>> m_transforms{};

    public:
        auto create_entity() const -> entity;
        auto destroy_entity(entity entity) const -> void;

        template <typename T>
        auto add(entity e, T comp) -> void
        {
            pool<T>().add(e, comp);
        }

        template<typename T>
        [[nodiscard]] auto get(entity e) -> T&
        {
            return pool<T>().get(e);
        }

        template<typename T>
        [[nodiscard]] auto pool() -> std::shared_ptr<component_pool<T>>;
    };

    template<>
    inline auto world::pool<transform>() -> std::shared_ptr<component_pool<transform>>
    {
        return m_transforms;
    }

    template<>
    inline auto world::pool<velocity>() -> std::shared_ptr<component_pool<velocity>>
    {
        return m_velocities;
    }
}
