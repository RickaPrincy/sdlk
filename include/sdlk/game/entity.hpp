//
// Created by ricka on 2026-05-20.
//
#pragma once

#include <cstdint>

namespace sdlk::game
{
    struct entity
    {
        uint32_t m_id;
        uint32_t m_generation;
    };

    inline auto pack(const entity e) -> uint64_t
    {
        return (static_cast<uint64_t>(e.m_generation) << 32) | e.m_id;
    }

    inline auto unpack(const uint64_t v) -> entity
    {
        return entity{
            static_cast<uint32_t>(v & 0xFFFFFFFF),
            static_cast<uint32_t>(v >> 32)
        };
    }

}
