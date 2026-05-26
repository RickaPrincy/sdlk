//
// Created by ricka on 2026-05-25.
//

#include <sdlk/game/serializer/scene_serializer.hpp>

#include "scene_serializer.hpp"
#include "../../utils/json_io.hpp"

namespace sdlk::engine::scene_serializer
{
    auto serialize(const project &project,  const std::shared_ptr<scene> &to_serialize) ->void
    {
        const auto canva_size = to_serialize->get_raw_scene()->get_canva_size();
        const json scene{
            {"name", to_serialize->get_name()},
            {"prefabs", json::array()},
            {"entities", json::array()},
            {"canva_size", {canva_size.x, canva_size.y} },
        };

        const auto scene_file_name = to_serialize->get_name() + SDLK_SCENES_EXTENSION;
        const auto scene_path = project.get_scenes_path() / scene_file_name;

        json_io::write(scene_path, scene);
    }

    auto deserialize(const std::string& path) -> std::shared_ptr<scene>
    {
        std::string scene_name{};
        auto callback = [&scene_name](const json &json)
        {
            scene_name = json["name"];
        };
        auto raw = game::scene_serializer::deserialize(path, callback);
        return std::make_shared<scene>(scene_name, raw);
    }
}