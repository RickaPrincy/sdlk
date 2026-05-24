//
// Created by ricka on 2026-05-20.
//

#include <imgui.h>
#include "components.hpp"
#include "../../utils/imgui_drawer_utils.hpp"

namespace sdlk
{
    auto draw_home_options(const float content_width, bool &is_creating_new_project) -> void
    {
        static auto projects = get_last_projects();

        if (ImGui::Button("Create a new Project", ImVec2(content_width, 0)))
        {
            is_creating_new_project = true;
            return;
        }

        imgui_drawer_utils::spacing();
        if (ImGui::Button("Open a Project", ImVec2(content_width, 0)))
        {
            trigger_open_project();
        }

        imgui_drawer_utils::spacing();
        ImGui::Separator();
        imgui_drawer_utils::spacing();

        ImGui::Text("Last Projects");
        imgui_drawer_utils::spacing();

        constexpr float padding = 8.0f;
        constexpr float card_size = 140.0f;
        const float available_width = content_width;
        int times_per_row = static_cast<int>(available_width / (card_size + padding));

        if (times_per_row < 1)
        {
            times_per_row = 1;
        }

        for (int i = 0; i < projects.size(); ++i)
        {
            if (i != 0 && i % times_per_row != 0)
            {
                ImGui::SameLine(0, padding);
            }
            draw_project_card(projects[i]);
        }
    }
}