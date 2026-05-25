//
// Created by ricka on 2026-05-25.
//

#include "components.hpp"

namespace sdlk::engine::editor
{
    auto draw_right_sidebar(float width) -> void
    {
        ImGui::BeginChild("RightSidebar", ImVec2(width, 0), true);

        if (selected_scene_idx == -1)
        {
            ImGui::TextDisabled("No selection");
            ImGui::EndChild();
            return;
        }

        auto &[name, size] = scenes[selected_scene_idx];

        ImGui::Text("Scene Inspector");
        ImGui::Dummy(ImVec2(0.0f, 4.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 4.0f));

        if (ImGui::CollapsingHeader("Info", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 2.0f));
            ImGui::InputText("Name", name, IM_ARRAYSIZE(name));
            ImGui::Dummy(ImVec2(0.0f, 4.0f));
        }

        if (ImGui::CollapsingHeader("Appearance", ImGuiTreeNodeFlags_DefaultOpen))
        {
            ImGui::Dummy(ImVec2(0.0f, 2.0f));
            ImGui::DragFloat2("Size Layout", reinterpret_cast<float *>(&size), 1.0f, 100.0f, 4000.0f, "%.0f px");
            ImGui::Dummy(ImVec2(0.0f, 4.0f));
        }

        ImGui::EndChild();
    }

} // namespace sdlk::editor