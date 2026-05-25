//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <string>
#include <glm/vec2.hpp>

namespace sdlk::game
{
    struct project
    {
        std::string m_name{};
        std::string m_version{};
        std::string m_start_scene{};
        glm::vec2 m_window_size{800};
    };
}