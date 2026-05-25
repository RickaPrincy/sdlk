//
// Created by ricka on 2026-05-25.
//

#include <cstdio>
#include <thread>
#include <filesystem>
#include <any>

#include "components.hpp"
#include "../../project.hpp"

#define BIN_PATH "build/vcpkg-release/bin/sdlkgame"

namespace sdlk::engine::editor
{
    static FILE* external_process = nullptr;

    static auto get_bin_path(const context_getter& context_getter) -> std::string
    {
        auto& [props] = context_getter();
        const auto& current_project = std::any_cast<project&>(props["project"]);
        return (std::filesystem::path(current_project.m_path) / BIN_PATH).string();
    }

    auto draw_viewport(const float width, const context_getter& context_getter) -> void
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.0f, 8.0f));
        ImGui::BeginChild("ViewportCenter", ImVec2(width, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

        if (selected_scene_idx == -1)
        {
            ImGui::TextDisabled("No scene selected");
            ImGui::EndChild();
            ImGui::PopStyleVar();
            return;
        }

        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 4.0f);
        if (is_playing)
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.55f, 0.15f, 0.15f, 1.0f));
            if (ImGui::Button("Stop", ImVec2(70, 0)))
            {
                if (external_process != nullptr)
                {
                    const auto path = get_bin_path(context_getter);
                    std::system(std::string("pkill -f " + path).c_str());
                    pclose(external_process);
                    external_process = nullptr;
                }
                is_playing = false;
            }
            ImGui::PopStyleColor();
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.45f, 0.15f, 1.0f));
            if (ImGui::Button("Run", ImVec2(70, 0)))
            {
                is_playing = true;

                const auto path = get_bin_path(context_getter);
                std::thread([path]() {
                    external_process = popen(path.c_str(), "w");
                    if (!external_process)
                    {
                        is_playing = false;
                    }
                })
                .detach();
            }
            ImGui::PopStyleColor();
        }

        ImGui::SameLine();
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 2.0f);
        ImGui::TextDisabled("| Active Canvas Workspace");

        ImGui::Dummy(ImVec2(0.0f, 2.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 6.0f));

        auto&[name, size] = scenes[selected_scene_idx];
        if (const ImVec2 avail = ImGui::GetContentRegionAvail(); avail.x > size.x)
        {
            ImGui::SetCursorPosX((avail.x - size.x) * 0.5f);
        }

        ImGui::Button("##fixed_viewport_canvas", size);

        ImGui::EndChild();
        ImGui::PopStyleVar();
    }
} // namespace sdlk::engine::editor