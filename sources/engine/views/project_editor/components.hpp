#pragma once

#include <imgui.h>

namespace sdlk::engine::editor
{
    struct scene_data
    {
        char name[64];
        ImVec2 size;
    };

    extern int selected_scene_idx;
    extern bool is_playing;
    extern scene_data scenes[3];

    auto draw_top_bar() -> void;
    auto draw_left_sidebar(float width) -> void;
    auto draw_viewport(float width) -> void;
    auto draw_right_sidebar(float width) -> void;
} // namespace sdlk::editor