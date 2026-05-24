//
// Created by ricka on 2026-05-24.
//

#pragma once

#include <memory>
#include <sdlk/core/2d/shape/shape.hpp>

namespace sdlk::game
{
    struct mesh
    {
        std::shared_ptr<sdlk2d::shape> m_shape{};
    };
}
