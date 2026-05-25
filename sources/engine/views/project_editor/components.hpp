#pragma once

#include <functional>
#include <imgui.h>

#include <sdlk/core/renderable.hpp>

namespace sdlk::engine::editor
{
    using context_getter = std::function<renderable_context&()>;

    struct scene_data
    {
        char name[64];
        ImVec2 size;
    };

    extern int selected_scene_idx;
    extern bool is_playing;
    extern scene_data scenes[3];

    auto draw_top_bar() -> void;
    auto draw_right_sidebar(float width) -> void;
    auto draw_viewport(float width, const context_getter& context_getter) -> void;
    auto draw_left_sidebar(float width, const context_getter& context_getter) -> void;

    auto draw_left_project_section(const context_getter& context_getter) -> void;
} // namespace sdlk::editor