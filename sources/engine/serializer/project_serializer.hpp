//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <string>
#include "../types/project.hpp"

namespace sdlk::engine::project_serializer
{
    auto serialize(const project& to_serialize) -> void;
    [[nodiscard]] auto deserialize(const std::string& path) -> project;
}