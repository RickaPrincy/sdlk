//
// Created by ricka on 2026-05-20.
//

#include <string>
#include <imgui.h>
#include <filesystem>
#include <memory>
#include "../../utils/nfd_wrapper.hpp"
#include <regex>

#include "components.hpp"

namespace sdlk
{
    static auto is_valid_project_name(const std::string& name) -> bool
    {
        static const std::regex pattern("^[a-zA-Z0-9_-]{3,32}$");
        return std::regex_match(name, pattern);
    }

    auto draw_create_project(const float content_width, bool& is_creating_new_project) -> void
    {
        static std::string project_name;
        static std::filesystem::path selected_folder;

        const bool name_valid = is_valid_project_name(project_name);
        const bool folder_valid = !selected_folder.empty();
        const bool can_create = name_valid && folder_valid;

        ImGui::Spacing();
        ImGui::Text("Create New Project");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Project name");
        char buffer[128] = {};
        std::snprintf(buffer, sizeof(buffer), "%s", project_name.c_str());
        ImGui::PushItemWidth(content_width);
        if (ImGui::InputText("##project_name", buffer, sizeof(buffer)))
        {
            project_name = buffer;
        }
        ImGui::PopItemWidth();

        if (!project_name.empty() && !name_valid)
        {
            ImGui::TextColored(ImVec4(1, 0.4f, 0.2f, 1),
                "Invalid name (3-32 chars, a-z A-Z 0-9 _ -)");
        }

        ImGui::Spacing();
        ImGui::Text("Location");
        if (ImGui::Button("Choose folder", ImVec2(content_width, 0)))
        {
            if (const auto res = nfd_wrapper::instance().open_folder_dialog(); res.m_type == nfd_open_dialog_result::type::success)
            {
                selected_folder = res.m_path.value();
            }
        }

        ImGui::TextDisabled("%s",
            selected_folder.empty()
                ? "No folder selected"
                : selected_folder.string().c_str());

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        const float btn_width = (content_width - 10.0f) * 0.5f;
        if (!can_create)
        {
            ImGui::BeginDisabled();
        }

        if (ImGui::Button("Create", ImVec2(btn_width, 0)))
        {
            trigger_new_project(selected_folder, project_name);
            project_name.clear();
            selected_folder.clear();
            is_creating_new_project = false;
        }

        if (!can_create)
        {
            ImGui::EndDisabled();
        }

        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(btn_width, 0)))
        {
            project_name.clear();
            selected_folder.clear();
            is_creating_new_project = false;
        }

        ImGui::Spacing();
        ImGui::TextDisabled("Allowed: 3-32 chars, letters, numbers, _ and -");
    }
}
