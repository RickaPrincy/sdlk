//
// Created by ricka on 2026-05-26.
//

#include "components.hpp"

namespace sdlk::engine::editor
{
    static auto get_scenes(const context_getter& context_getter) -> std::vector<std::shared_ptr<scene>>
    {
        auto &props = context_getter();
        return std::any_cast<std::vector<std::shared_ptr<scene>>>(props["scenes"]);
    }

    static auto map_scenes_names(const std::vector<std::shared_ptr<scene>> &scenes) -> std::vector<std::string>
    {
        std::vector<std::string> names{};
        names.reserve(scenes.size());
        for (const auto &scene : scenes)
        {
            names.emplace_back(scene->get_name());
        }
        return names;
    }

    auto draw_left_scenes_section(const context_getter& context_getter) -> void
    {
        auto selected_scene = get_selected_scene(context_getter);
        auto scenes = get_scenes(context_getter);
        const auto names = map_scenes_names(scenes);

        auto on_scene_click = [&scenes, &context_getter](const int selected_idx, const std::string &scene_name)
        {
            auto &props = context_getter();
            const auto scene = scenes[selected_idx];
            props["selected_item"] = scene;
        };

        auto is_scene_selected = [selected_scene](const std::string &scene_name) -> bool
        {
            if (!selected_scene) return false;
            return selected_scene->get_name() == scene_name;
        };

        draw_sidebar_section({
            .title = "Scenes",
            .items = names,
            .is_selected = is_scene_selected,
            .on_item_click = on_scene_click
        });
    }
}