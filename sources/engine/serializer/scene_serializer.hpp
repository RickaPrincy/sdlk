//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <string>
#include <memory>
#include "../types/scene.hpp"
#include "../types/project.hpp"

#define SDLK_SCENES_EXTENSION ".scene"

namespace sdlk::engine::scene_serializer
{
    auto serialize(const project &project, const std::shared_ptr<scene> &to_serialize) -> void;
    [[nodiscard]] auto deserialize(const std::string& path) -> std::shared_ptr<scene>;
}