//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <memory>
#include <string>
#include <nlohmann/json.hpp>
#include <sdlk/game/scenes/scene.hpp>

namespace sdlk::game::scene_serializer
{
    [[nodiscard]] auto deserialize(const std::string &path) -> std::shared_ptr<scene>;
    [[nodiscard]] auto deserialize(const std::string &path, const std::function<void(const nlohmann::json &json)> &callback) -> std::shared_ptr<scene>;
}
