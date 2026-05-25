//
// Created by ricka on 2026-05-25.
//
#include "components.hpp"

namespace sdlk::engine::editor
{
    auto draw_top_bar() -> void
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Projects"))
            {
                if (ImGui::MenuItem("Save Project")) {}
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

} // namespace sdlk::editor