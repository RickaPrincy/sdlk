//
// Created by ricka on 2026-05-25.
//

#include "../../../utils/json_io.hpp"
#include <sdlk/game/scenes/game_scene.hpp>
#include <sdlk/game/serializer/scene_serializer.hpp>

namespace sdlk::game::scene_serializer
{
    auto deserialize(const std::string &path) -> std::shared_ptr<scene>
    {
        static auto noop_callback  = [](const nlohmann::json &json) {};
        return deserialize(path, noop_callback);
    }

    //TODO: validate and add entities deserializer
    auto deserialize(const std::string &path, const std::function<void(const nlohmann::json &json)> &callback) ->
    std::shared_ptr<scene>
    {
        auto json = json_io::read(path);

        int canva_width = 2000;
        int canva_height = 2000;
        if (json.contains("canva_size") && json["canva_size"].is_array() && json["window_size"].size() >= 2)
        {
            canva_width = json["canva_size"][0].get<int>();
            canva_height = json["canva_size"][1].get<int>();
        }

        callback(json);
        return std::make_shared<game_scene>(glm::vec2{canva_width, canva_height});
    }
}
