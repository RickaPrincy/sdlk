//
// Created by ricka on 2026-05-17.
//

#include "../view.hpp"
#include <sdlk/core/imgui/imgui_renderable.hpp>
#include <imgui.h>

static auto draw_project_content(std::weak_ptr<sdlk::component> parent_view) -> std::function<void()>;

auto sdlk::project_editor() -> std::shared_ptr<component>
{
    auto project_view = std::make_shared<component>();
    auto content_drawer = draw_project_content(project_view);
    project_view->add_child(imgui_renderable::make(std::move(content_drawer)));
    return project_view;
}

auto draw_project_content(std::weak_ptr<sdlk::component> parent_view) -> std::function<void()>
{
    return [parent_view]() {
        if (const auto parent = parent_view.lock())
        {
            const auto project_name = parent->get_context<std::string>("project_name").value_or("None");
            ImGui::TextUnformatted(project_name.c_str());
        }
    };
}