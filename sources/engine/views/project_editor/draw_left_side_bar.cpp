//
// Created by ricka on 2026-05-25.
//

#include <imgui.h>
#include "components.hpp"

namespace sdlk::engine::editor
{
    auto draw_left_sidebar(const float width, const context_getter& context_getter) -> void
    {
        ImGui::BeginChild("LeftSidebar", ImVec2(width, 0), true);

        draw_left_scenes_section(context_getter);

        const float remaining_height = ImGui::GetContentRegionAvail().y;
        if (constexpr float projects_block_size = 55.0f; remaining_height > projects_block_size)
        {
            ImGui::Dummy(ImVec2(0.0f, remaining_height - projects_block_size));
        }

        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 2.0f));

        draw_left_project_section(context_getter);

        ImGui::EndChild();
    }
} // namespace sdlk::editor