//
// Created by ricka on 2026-05-20.
//

#include "components.hpp"
#include "../../conf/sdlk_engine_conf.hpp"

namespace sdlk
{
    auto get_last_projects() -> std::vector<std::shared_ptr<project>>
    {
       std::vector<std::shared_ptr<project>> projects{};
	    projects.reserve(sdlk_engine_conf::MAX_RECENTS);

        const auto last_project_paths = sdlk_engine_conf::load_or_init()->get_last_project_paths();
	    for (const auto& path : last_project_paths)
	    {
	       projects.emplace_back(std::make_shared<project>(path));
	    }
	    return projects;
    }
}
