//
// Created by ricka on 2026-05-20.
//

#pragma once

#include <vector>
#include <sdlk/game/entity.hpp>

namespace sdlk
{
    class entity_manager
    {
        uint32_t m_next = 0;
        std::vector<uint32_t> m_free;
        std::vector<uint32_t> m_generation;
    public:
        auto create() -> entity;
        auto destroy(entity e) -> void;

        [[nodiscard]] auto valid(entity e) const -> bool;
    };
}