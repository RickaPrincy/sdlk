//
// Created by ricka on 2026-02-06.
//

#include <imgui.h>
#include "components.hpp"
#include "../../loader/project_loader.hpp"

namespace sdlk::engine::home_view
{
    auto draw_project_card(const project& project) -> void
    {
        ImGui::Dummy(ImVec2(0, 6));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12.0f, 12.0f));

        ImGui::BeginChild(
            project.m_name.c_str(),
            ImVec2(0, 52),
            true,
            ImGuiWindowFlags_None
        );

        ImGui::AlignTextToFramePadding();
        ImGui::TextUnformatted(project.m_name.c_str());

        ImGui::SameLine();

        constexpr float buttonWidth = 80.0f;
        const float avail = ImGui::GetContentRegionAvail().x;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + avail - buttonWidth);

        if (ImGui::Button("Open", ImVec2(buttonWidth, 0)))
        {
            project_loader::load(project);
        }

        ImGui::EndChild();
        ImGui::PopStyleVar();

        ImGui::Dummy(ImVec2(0, 6));
    }
}  // namespace sdlk