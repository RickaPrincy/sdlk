//
// Created by ricka on 2026-02-06.
//

#pragma once

#include <memory>
#include <vector>

#include "../../types/project.hpp"

namespace sdlk
{
    auto trigger_open_project() -> void;
    auto trigger_new_project(const std::string &path, const std::string &name) -> void;
    [[nodiscard]] auto get_last_projects() -> std::vector<std::shared_ptr<project>>;

    auto draw_home_options(float content_width, bool &is_creating_new_project) -> void;
    auto draw_create_project(float content_width, bool &is_creating_new_project) -> void;
    auto draw_project_card(const std::shared_ptr<project>& project) -> void;
}
