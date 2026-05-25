//
// Created by ricka on 2026-05-17.
//

#include <sdlk/core/imgui/imgui_renderable.hpp>

#include "../view.hpp"
#include "components.hpp"

static auto draw_editor_root() -> std::function<void()>
{
    return []()
    {
        sdlk::engine::editor::draw_top_bar();

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        ImGui::Begin("Engine Editor Workspace", nullptr,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);

        constexpr auto left_panel_width = 230.0f;
        constexpr float right_panel_width = 270.0f;
        const float center_viewport_width = ImGui::GetContentRegionAvail().x - left_panel_width - right_panel_width - (ImGui::GetStyle().ItemSpacing.x * 2.0f);

        sdlk::engine::editor::draw_left_sidebar(left_panel_width);

        ImGui::SameLine();
        sdlk::engine::editor::draw_viewport(center_viewport_width);

        ImGui::SameLine();
        sdlk::engine::editor::draw_right_sidebar(right_panel_width);

        ImGui::End();
    };
}

auto sdlk::engine::project_editor() -> std::shared_ptr<component>
{
    auto view = std::make_shared<component>();
    view->add_child(imgui_renderable::make(draw_editor_root()));
    return view;
}