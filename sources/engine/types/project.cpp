//
// Created by ricka on 2026-02-06.
//

#include "project.hpp"

#include <iostream>
#include <stdexcept>
#include <utility>
#include <nlohmann/json.hpp>
#include "../utils/json_reader.hpp"
#include <sdlk/core/app.hpp>
#include "../conf/sdlk_engine_conf.hpp"

#define SDLK_PROJECT_FILE_CONF_NAME "sdlk_engine.json"
using json = nlohmann::json;

namespace sdlk
{
	project::project(std::string path)
	{
	    this->m_path = std::move(path);
	    const auto file_path = std::filesystem::path(this->m_path);
	    auto project_conf = json_reader::read(file_path / SDLK_PROJECT_FILE_CONF_NAME);
	    this->m_name = project_conf["name"];
	}

    auto project::open() const -> void
	{
	    const auto engine = app::get();
	    const auto project_editor_context = std::make_shared<renderable_context>();
	    project_editor_context->set<std::string>("project_name", this->m_name);

	    sdlk_engine_conf::load_or_init()->add_recent_project(this->m_path);
	    engine->switch_to("project_editor", project_editor_context);
	    std::cout << "Project opened: " << this->m_name << std::endl;
	}

	auto project::get_name() -> std::string
	{
		return this->m_name;
	}

    auto project::get_path() -> std::string
    {
        return this->m_path;
    }
}  // namespace sdlk