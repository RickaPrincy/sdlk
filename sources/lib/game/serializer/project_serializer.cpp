//
// Created by ricka on 2026-05-25.
//

#include <sdlk/game/serializer/project_serializer.hpp>
#include "../../../utils/json_io.hpp"

namespace sdlk::game::project_serializer
{
    //TODO: validate
    auto deserialize(const std::string &path) -> project
    {
        const auto json = json_io::read(path);
        const auto name = json["name"].get<std::string>();
        const auto version = json["version"].get<std::string>();
        const auto start_scene = json["start_scene"].get<std::string>();

        int window_width = 1280;
        int window_height = 720;
        if (json.contains("window_size") && json["window_size"].is_array() && json["window_size"].size() >= 2)
        {
            window_width = json["window_size"][0].get<int>();
            window_height = json["window_size"][1].get<int>();
        }

        return {
            name,
            version,
            start_scene,
            glm::vec2{window_width, window_height},
        };
    }
}
