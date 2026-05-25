//
// Created by ricka on 2026-05-25.
//

#include "components.hpp"
#include <vector>
#include <string>
#include <functional>

namespace sdlk::engine::editor
{
    struct sidebar_section_args
    {
        const char* title;
        const std::vector<std::string>& items;
        int& selected_idx;
        std::function<void(int, const std::string&)> on_item_click = nullptr;
        std::function<void()> on_add_click = nullptr;
    };

    static auto draw_sidebar_section(const sidebar_section_args& args) -> void
    {
        if (ImGui::TreeNodeEx(args.title, 0))
        {
            if (args.items.empty())
            {
                ImGui::TextDisabled("  Empty");
            }
            else
            {
                for (int i = 0; i < static_cast<int>(args.items.size()); i++)
                {
                    if (ImGui::Selectable(args.items[i].c_str(), args.selected_idx == i))
                    {
                        args.selected_idx = i;
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

    auto draw_left_sidebar(const float width) -> void
    {
        ImGui::BeginChild("LeftSidebar", ImVec2(width, 0), true);

        static std::vector<std::string> files_list;
        static int selected_file_idx = -1;
        draw_sidebar_section({
            .title = "Files",
            .items = files_list,
            .selected_idx = selected_file_idx
        });

        std::vector<std::string> scene_names;
        for (const auto&[name, size] : scenes)
        {
            scene_names.push_back(name);
        }

        draw_sidebar_section({
            .title = "Scenes",
            .items = scene_names,
            .selected_idx = selected_scene_idx
        });

        static std::vector<std::string> entities_list;
        static int selected_entity_idx = -1;
        draw_sidebar_section({
            .title = "Entities",
            .items = entities_list,
            .selected_idx = selected_entity_idx
        });

        static std::vector<std::string> prefabs_list;
        static int selected_prefab_idx = -1;
        draw_sidebar_section({
            .title = "Prefabs",
            .items = prefabs_list,
            .selected_idx = selected_prefab_idx
        });

        const float remaining_height = ImGui::GetContentRegionAvail().y;
        if (constexpr float projects_block_size = 55.0f; remaining_height > projects_block_size)
        {
            ImGui::Dummy(ImVec2(0.0f, remaining_height - projects_block_size));
        }

        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 2.0f));

        static std::vector<std::string> projects_list;
        static int selected_project_idx = -1;

        draw_sidebar_section({
            .title = "Projects",
            .items = projects_list,
            .selected_idx = selected_project_idx
        });

        ImGui::EndChild();
    }
} // namespace sdlk::editor