//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <sdlk/game/project.hpp>

namespace sdlk::game::project_serializer
{
    [[nodiscard]] auto deserialize(const std::string& path) -> project;
}