//
// Created by ricka on 2026-05-26.
//

#include <imgui.h>
#include "components.hpp"

namespace sdlk::engine::editor
{
    auto draw_sidebar_section(const sidebar_section_args& args) -> void
    {
        if (ImGui::TreeNodeEx(args.title, 0))
        {
            if (args.items.empty())
            {
                ImGui::TextDisabled("Empty");
            }
            else
            {
                for (int i = 0; i < static_cast<int>(args.items.size()); i++)
                {
                    auto is_selected = args.is_selected(args.items[i]);
                    if (ImGui::Selectable(args.items[i].c_str()), is_selected)
                    {
                        if (args.on_item_click)
                        {
                            args.on_item_click(i, args.items[i]);
                        }
                    }
                }
            }

            ImGui::Dummy(ImVec2(0.0f, 2.0f));
            if (ImGui::Button("Add", ImVec2(-1, 0)))
            {
                if (args.on_add_click)
                {
                    args.on_add_click();
                }
            }
            ImGui::TreePop();
        }
        ImGui::Dummy(ImVec2(0.0f, 4.0f));
    }
}