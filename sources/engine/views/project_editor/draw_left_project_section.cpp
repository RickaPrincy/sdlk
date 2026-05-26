//
// Created by ricka on 2026-05-25.
//

#include "components.hpp"
#include "../../types/project.hpp"
#include "../../serializer/project_serializer.hpp"
#include "../../validator/project_validator.hpp"

#include <imgui.h>
#include <any>

namespace sdlk::engine::editor
{
    auto draw_left_project_section(const context_getter& context_getter) -> void
    {
        auto& props = context_getter();
        auto& current_project = std::any_cast<project&>(props["project"]);

        if (ImGui::TreeNode("Project"))
        {
            ImGui::PushItemWidth(-1);

            static char project_name[256]{};
            static char version[64]{};
            static char start_scene[512]{};
            static std::string last_project_path{};

            static validation_result validation;
            static bool needs_validation = true;

            if (last_project_path != current_project.m_path)
            {
                std::snprintf(project_name, sizeof(project_name), "%s", current_project.m_name.c_str());
                std::snprintf(version, sizeof(version), "%s", current_project.m_version.c_str());
                std::snprintf(start_scene, sizeof(start_scene), "%s", current_project.m_start_scene.c_str());
                last_project_path = current_project.m_path;
                needs_validation = true;
            }

            ImGui::TextUnformatted("Name");
            if (ImGui::InputText("##project_name", project_name, sizeof(project_name)))
            {
                current_project.m_name = project_name;
                needs_validation = true;
            }

            ImGui::Dummy(ImVec2(0, 4));

            ImGui::TextUnformatted("Version");
            if (ImGui::InputText("##version", version, sizeof(version)))
            {
                current_project.m_version = version;
                needs_validation = true;
            }

            ImGui::Dummy(ImVec2(0, 4));

            ImGui::TextUnformatted("Main Scene");
            if (ImGui::InputText("##start_scene", start_scene, sizeof(start_scene)))
            {
                current_project.m_start_scene = start_scene;
                needs_validation = true;
            }

            ImGui::Dummy(ImVec2(0, 6));

            ImGui::TextUnformatted("Window Width");
            int width = static_cast<int>(current_project.m_window_size.x);
            if (ImGui::InputInt("##width", &width))
            {
                current_project.m_window_size.x = static_cast<float>(width);
                needs_validation = true;
            }

            ImGui::Dummy(ImVec2(0, 4));

            ImGui::TextUnformatted("Window Height");
            int height = static_cast<int>(current_project.m_window_size.y);
            if (ImGui::InputInt("##height", &height))
            {
                current_project.m_window_size.y = static_cast<float>(height);
                needs_validation = true;
            }

            ImGui::Dummy(ImVec2(0, 6));

            if (needs_validation)
            {
                validation = project_validator::validate(current_project);
                needs_validation = false;
            }

            ImGui::BeginDisabled(!validation.m_valid);
            if (ImGui::Button("Save", ImVec2(-1, 0)))
            {
                project_serializer::serialize(current_project);
            }
            ImGui::EndDisabled();

            ImGui::PopItemWidth();
            ImGui::TreePop();
        }
    }
}