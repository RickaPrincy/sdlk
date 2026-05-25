//
// Created by ricka on 2026-05-25.
//

#include "../project.hpp"

#include "project_serializer.hpp"
#include <sdlk/game/serializer/project_serializer.hpp>

#define SDLK_RESOURCES_FOLDER "resources"
#define SDLK_PROJECT_FILE_CONF_NAME "sdlkgame.sdlkproj"

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

        json project_conf{
            {"name", to_serialize.m_name},
            {"version", to_serialize.m_version},
            {"start_scene", to_serialize.m_start_scene},
            {"window_size", {to_serialize.m_window_size.x, to_serialize.m_window_size.y}}
        };

        const auto file_path = project_dir / SDLK_RESOURCES_FOLDER / SDLK_PROJECT_FILE_CONF_NAME;
        std::ofstream file(file_path);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open project file for saving");
        }
        file << project_conf.dump(2);
    }

    auto project_serializer::deserialize(const std::string &path) -> project
    {
        const std::filesystem::path project_dir(path);
        const auto file_path = project_dir / SDLK_RESOURCES_FOLDER / SDLK_PROJECT_FILE_CONF_NAME;
        const auto [
            m_name,
            m_version,
            m_start_scene,
            m_window_size] = game::project_serializer::deserialize(file_path);

        return project{
            .m_path = path,
            .m_name = m_name,
            .m_version = m_version,
            .m_window_size = m_window_size,
            .m_start_scene = m_start_scene,
        };
    }
}
