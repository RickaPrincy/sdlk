#pragma once

#include <any>
#include <optional>
#include <functional>
#include <sdlk/core/renderable.hpp>
#include "../../types/scene.hpp"

namespace sdlk::engine::editor
{
    struct sidebar_section_args
    {
        const char* title;
        const std::vector<std::string>& items;
        std::function<void()> on_add_click = nullptr;
        std::function<bool(const std::string&)> is_selected;
        std::function<void(int, const std::string&)> on_item_click = nullptr;
    };
    using context_getter = std::function<std::unordered_map<std::string, std::any>&()>;

    auto draw_top_bar() -> void;
    auto draw_right_sidebar(float width, const context_getter& context) -> void;
    auto draw_viewport(float width, const context_getter& context_getter) -> void;
    auto draw_left_sidebar(float width, const context_getter& context_getter) -> void;

    auto draw_sidebar_section(const sidebar_section_args& args) -> void;
    auto draw_left_scenes_section(const context_getter& context_getter) -> void;
    auto draw_left_project_section(const context_getter& context_getter) -> void;

    auto get_selected_scene(const context_getter& context_getter) -> std::shared_ptr<scene>;
    auto get_selected_item(const context_getter& context_getter) -> std::optional<std::any>;
} // namespace sdlk::editor