//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <glm/vec2.hpp>

#define SDLK_SCENES_FOLDER "scenes"
#define SDLK_RESOURCES_FOLDER "resources"

namespace sdlk::engine
{
    struct project
    {
        std::string m_path{};
        std::string m_name{};
        std::string m_version{"0.0.1"};
        glm::vec2 m_window_size{800, 700};
        std::string m_start_scene{"resources/scenes/main.scene"};

        [[nodiscard]] auto get_scenes_path() const -> std::filesystem::path
        {
            return std::filesystem::path(m_path) / SDLK_RESOURCES_FOLDER / SDLK_SCENES_FOLDER;
        }
    };
}
