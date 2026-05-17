//
// Created by ricka on 2026-05-17.
//

#include "../view.hpp"
#include <sdlk/core/imgui/imgui_renderable.hpp>
#include <imgui.h>

static auto draw_project_content(sdlk::renderable*) -> void;

auto sdlk::project_editor() -> std::shared_ptr<component>
{
    auto project_view = std::make_shared<component>();
    project_view->add_child(imgui_renderable::make(&draw_project_content));
    return project_view;
}

auto draw_project_content(sdlk::renderable *_renderable) -> void
{
    auto project_name = _renderable->get_context<std::string>("project_name");
    ImGui::Text("Last Projects");
}
