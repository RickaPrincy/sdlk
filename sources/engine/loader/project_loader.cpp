//
// Created by ricka on 2026-05-25.
//

#include "project_loader.hpp"
#include "scene_loader.hpp"

#include <sdlk/core/app.hpp>
#include <sdlk/core/renderable.hpp>

#include "../sdlk_engine_conf.hpp"

namespace sdlk::engine::project_loader
{
    auto load(project to_load) -> void
    {
        const auto engine = app::get();

        renderable_context project_editor_context{};
        project_editor_context.set<project>("project", to_load);
        project_editor_context.set<std::string>("project_name", to_load.m_name);

        const auto scenes  = scene_loader::load(to_load);
        project_editor_context.set<std::vector<std::shared_ptr<scene>>>("scenes", scenes);

        sdlk_engine_conf::load_or_init()->add_recent_project(to_load.m_path);
        engine->switch_to("project_editor", project_editor_context);
    }
}
