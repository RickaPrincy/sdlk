//
// Created by ricka on 2026-05-20.
//

#include "components.hpp"
#include "../../sdlk_engine_conf.hpp"
#include "../../serializer/project_serializer.hpp"

namespace sdlk::engine::home_view
{
    auto get_last_projects() -> std::vector<project>
    {
        std::vector<project> projects{};
	    projects.reserve(sdlk_engine_conf::MAX_RECENTS);

        const auto last_project_paths = sdlk_engine_conf::load_or_init()->get_last_project_paths();
	    for (const auto& path : last_project_paths)
	    {
	       projects.emplace_back(project_serializer::deserialize(path));
	    }
	    return projects;
    }
}
