//
// Created by ricka on 2026-05-25.
//

#include <imgui.h>
#include "components.hpp"

namespace sdlk::engine::editor
{
    auto draw_top_bar() -> void
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Projects"))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

} // namespace sdlk::editor