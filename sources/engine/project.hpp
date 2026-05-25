//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <string>
#include <glm/vec2.hpp>
#include "../utils/json_reader.hpp"

//TODO
namespace sdlk::engine
{
    struct project
    {
        std::string m_path{};
        std::string m_name{};
        std::string m_version{"0.0.1"};
        glm::vec2 m_window_size{800, 700};
        std::string m_start_scene{"resources/scenes/main.scene"};
    };
}
