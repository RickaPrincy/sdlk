//
// Created by ricka on 2026-05-25.
//

#include "../project.hpp"

#include "project_serializer.hpp"
#define SDLK_PROJECT_FILE_CONF_NAME "sdlk_engine.json"

using json = nlohmann::json;
namespace sdlk::engine
{
    auto project_serializer::serialize(const project &to_serialize) -> void
    {
        const auto name = to_serialize.m_name;
        const auto path = to_serialize.m_path;

        if (path.empty() || name.empty())
        {
            throw std::runtime_error("Cannot save project: empty path or empty name");
        }

        const std::filesystem::path project_dir(path);
        if (!std::filesystem::exists(project_dir))
        {
            throw std::runtime_error("Cannot save project: directory does not exist");
        }

        json project_conf;
        project_conf["name"] = name;

        const auto file_path = project_dir / SDLK_PROJECT_FILE_CONF_NAME;
        std::ofstream file(file_path);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open project file for saving");
        }
        file << project_conf.dump(2);
    }

    auto project_serializer::deserialize(const std::string &path) -> project
    {
        const auto file_path = std::filesystem::path(path);
        auto project_conf = json_reader::read(file_path / SDLK_PROJECT_FILE_CONF_NAME);
        return project{project_conf["name"], path};
    }
}
