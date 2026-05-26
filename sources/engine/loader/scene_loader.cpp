//
// Created by ricka on 2026-05-25.
//

#include "scene_loader.hpp"

#include "../serializer/scene_serializer.hpp"

namespace fs = std::filesystem;

auto sdlk::engine::scene_loader::load(const project &project) -> std::vector<std::shared_ptr<scene>>
{
    std::vector<std::shared_ptr<scene>> scenes{};
    const auto scenes_path = project.get_scenes_path();

    if (!fs::exists(scenes_path) || !fs::is_directory(scenes_path))
    {
        return scenes;
    }

    for (const auto& entry : fs::directory_iterator(scenes_path))
    {
        if (entry.is_regular_file() && entry.path().extension() == SDLK_SCENES_EXTENSION)
        {
            auto new_scene =  scene_serializer::deserialize(entry.path().string());
            scenes.push_back(new_scene);
        }
    }

    return scenes;
}
