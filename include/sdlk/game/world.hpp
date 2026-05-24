//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <sdlk/game/entity.hpp>
#include <sdlk/game/component_pool.hpp>
#include <sdlk/game/entity_manager.hpp>
#include <sdlk/game/components/transform.hpp>
#include <sdlk/game/components/velocity.hpp>
#include <sdlk/game/components/texture.hpp>
#include <sdlk/game/components/mesh.hpp>

namespace sdlk::game
{
    class world
    {
        entity_manager m_entity_manager{};

        component_pool<mesh> m_meshes{};
        component_pool<texture> m_textures{};
        component_pool<velocity> m_velocities{};
        component_pool<transform> m_transforms{};

    public:
        [[nodiscard]] auto create_entity() -> entity;
        auto destroy_entity(entity entity) -> void;

        template <typename T>
        auto add(entity e, T &comp) -> void
        {
            pool<T>().add(e, comp);
        }

        template<typename T>
        [[nodiscard]] auto get(entity e) -> T&
        {
            return pool<T>().get(e);
        }

        template<typename T>
        [[nodiscard]] auto pool() -> component_pool<T>&;

        world() = default;
    };

    template<>
    inline auto world::pool<transform>() -> component_pool<transform>&
    {
        return m_transforms;
    }

    template<>
    inline auto world::pool<velocity>() -> component_pool<velocity>&
    {
        return m_velocities;
    }

    template<>
    inline auto world::pool<mesh>() -> component_pool<mesh>&
    {
        return m_meshes;
    }

    template<>
    inline auto world::pool<texture>() -> component_pool<texture>&
    {
        return m_textures;
    }
}
