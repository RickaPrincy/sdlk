//
// Created by ricka on 2026-05-17.
//

#include <sdlk/core/component.hpp>
#include <sdlk/core/imgui/imgui_renderable.hpp>

#include "../view.hpp"
#include "components.hpp"
#include <imgui.h>

static auto draw_editor_root_content(const sdlk::engine::editor::context_getter &context_getter) -> std::function<void()>
{
    return [context_getter]()
    {
        sdlk::engine::editor::draw_top_bar();

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        ImGui::Begin("Engine Editor Workspace", nullptr,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);

        if (constexpr ImGuiTableFlags table_flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendY; ImGui::BeginTable("WorkspaceTable", 3, table_flags, ImGui::GetContentRegionAvail()))
        {
            ImGui::TableSetupColumn("Left", ImGuiTableColumnFlags_WidthFixed, 230.0f);
            ImGui::TableSetupColumn("Center", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Right", ImGuiTableColumnFlags_WidthFixed, 270.0f);

            ImGui::TableNextColumn();
            float left_width = ImGui::GetContentRegionAvail().x;
            if (left_width < 150.0f) left_width = 150.0f;
            sdlk::engine::editor::draw_left_sidebar(left_width, context_getter);

            ImGui::TableNextColumn();
            float center_width = ImGui::GetContentRegionAvail().x;
            if (center_width < 300.0f) center_width = 300.0f;
            sdlk::engine::editor::draw_viewport(center_width, context_getter);

            ImGui::TableNextColumn();
            float right_width = ImGui::GetContentRegionAvail().x;
            if (right_width < 180.0f) right_width = 180.0f;
            sdlk::engine::editor::draw_right_sidebar(right_width);

            ImGui::EndTable();
        }
        ImGui::End();
    };
}

static auto draw_editor_root(const std::weak_ptr<sdlk::component> &view) -> std::function<void()>
{
    const sdlk::engine::editor::context_getter context_getter = [view]() -> sdlk::renderable_context&
    {
        return view.lock()->get_context();
    };

    return draw_editor_root_content(context_getter);
}

auto sdlk::engine::project_editor() -> std::shared_ptr<component>
{
    auto view = std::make_shared<component>();
    view->add_child(imgui_renderable::make(draw_editor_root(view)));
    return view;
}