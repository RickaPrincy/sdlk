//
// Created by ricka on 2026-05-17.
//

#include "../view.hpp"
#include <sdlk/core/imgui/imgui_renderable.hpp>
#include <imgui.h>
#include <iostream>
#include <ostream>

#include "sdlk/core/components/2d/fonts/msdf_font.hpp"
#include "sdlk/core/components/2d/shape/text_shape.hpp"

static auto draw_project_content(std::weak_ptr<sdlk::component> parent_view) -> std::function<void()>;

auto sdlk::project_editor() -> std::shared_ptr<component>
{
    auto project_view = std::make_shared<component>();
    const auto content_drawer = draw_project_content(project_view);

    project_view->add_child(imgui_renderable::make(content_drawer));
    project_view->add_event_listener(event_type::key_down, [](const auto& event) {
        std::cout << "Key down" << std::endl;
    });
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