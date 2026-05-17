//
// Created by ricka on 2026-02-06.
//

#include <imgui.h>

#include "components.hpp"

namespace sdlk
{
    auto draw_project_card(const std::shared_ptr<project>& project) -> void
    {
        ImGui::Dummy(ImVec2(0, 6));
        ImGui::BeginChild(
            project->get_name().c_str(),
            ImVec2(0, 68),
            true,
            ImGuiWindowFlags_None
        );

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
        ImGui::TextUnformatted(project->get_name().c_str());
        ImGui::SameLine();

        constexpr float buttonWidth = 80.0f;
        const float avail = ImGui::GetContentRegionAvail().x;

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + avail - buttonWidth);
        if (ImGui::Button("Open", ImVec2(buttonWidth, 0)))
        {
            project->open();
        }

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Dummy(ImVec2(0, 6));
    }
}  // namespace sdlk
