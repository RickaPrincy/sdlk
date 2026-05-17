//
// Created by ricka on 2026-02-06.
//

#include "project.hpp"

#include <stdexcept>
#include <utility>
#include <nlohmann/json.hpp>
#include "../utils/json_reader.hpp"

#define SDLK_PROJECT_FILE_CONF_NAME "sdlk_engine.conf"
using json = nlohmann::json;

namespace sdlk
{
	project::project(std::string path)
	{
	    this->m_path = std::move(path);
	    const auto file_path = std::filesystem::path(path);
	    auto project_conf = json_reader::read(file_path / SDLK_PROJECT_FILE_CONF_NAME);
	    this->m_name = project_conf["name"];
	}

    auto project::open() -> void
	{
		throw std::runtime_error("Not implemented");
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