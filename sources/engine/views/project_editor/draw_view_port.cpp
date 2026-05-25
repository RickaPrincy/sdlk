//
// Created by ricka on 2026-05-25.
//

#include "components.hpp"

namespace sdlk::engine::editor
{
    auto draw_viewport(const float width) -> void
    {
        ImGui::BeginChild("ViewportCenter", ImVec2(width, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

        if (selected_scene_idx == -1)
        {
            ImGui::TextDisabled("No scene selected");
            ImGui::EndChild();
            return;
        }

        ImGui::PushStyleColor(ImGuiCol_Button, is_playing ? ImVec4(0.15f, 0.40f, 0.15f, 1.0f) : ImGui::GetStyle().Colors[ImGuiCol_Button]);
        if (ImGui::Button(is_playing ? "Playing" : "Play", ImVec2(65, 22))) { is_playing = true; }
        ImGui::PopStyleColor();

        ImGui::SameLine();
        ImGui::PushStyleColor(ImGuiCol_Button, !is_playing ? ImVec4(0.40f, 0.15f, 0.15f, 1.0f) : ImGui::GetStyle().Colors[ImGuiCol_Button]);
        if (ImGui::Button("Pause", ImVec2(65, 22))) { is_playing = false; }
        ImGui::PopStyleColor();

        ImGui::SameLine();
        ImGui::TextDisabled("| Active Canvas Workspace");
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 4.0f));

        auto&[name, size] = scenes[selected_scene_idx];
        if (const ImVec2 avail = ImGui::GetContentRegionAvail(); avail.x > size.x)
        {
            ImGui::SetCursorPosX((avail.x - size.x) * 0.5f);
        }

        ImGui::Button("##fixed_viewport_canvas", size);

        ImGui::EndChild();
    }

} // namespace sdlk::editor