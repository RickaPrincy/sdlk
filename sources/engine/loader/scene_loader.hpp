//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <memory>
#include <vector>

#include "../types/project.hpp"
#include "../types/scene.hpp"

namespace sdlk::engine::scene_loader
{
    [[nodiscard]] auto load(const project &project) -> std::vector<std::shared_ptr<scene>>;
}
