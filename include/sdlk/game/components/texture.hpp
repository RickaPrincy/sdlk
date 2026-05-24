//
// Created by ricka on 2026-05-24.
//

#pragma once

#include <memory>
#include <glm/vec3.hpp>
#include <sdlk/core/gl/gl_texture.hpp>

namespace sdlk::game
{
    struct texture
    {
        glm::vec3 m_uv_offset{0.0};
        std::shared_ptr<gl_texture> m_texture{};
    };
}
