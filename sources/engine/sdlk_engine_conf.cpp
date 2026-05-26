//
// Created by ricka on 2026-05-17.
//

#include "sdlk_engine_conf.hpp"

#include <utility>
#include <algorithm>
#include <nlohmann/json.hpp>

#include "utils/os.hpp"
#include "../utils/json_io.hpp"

#define SDLK_CONF_DIRECTORY ".sdlk-engine"
#define SDLK_CONF_FILE "sdlk-engine.conf.json"
#define SDLK_TEMPLATE_DIRECTORY "template-release"

using json = nlohmann::json;
namespace sdlk::engine
{
    sdlk_engine_conf::sdlk_engine_conf(std::string version, const std::vector<std::string> &last_projects)
        : m_version(std::move(version)), m_last_project_paths(last_projects)
    {}

    auto sdlk_engine_conf::get_config_path() -> std::filesystem::path
    {
        const auto home_path =  std::filesystem::path(os::get_home_dir());
        return home_path / SDLK_CONF_DIRECTORY;
    }

    auto sdlk_engine_conf::get_file_path() -> std::filesystem::path
    {
        const auto home_path =  std::filesystem::path(os::get_home_dir());
        return get_config_path() / SDLK_CONF_FILE;
    }

    auto sdlk_engine_conf::get_template_path() -> std::filesystem::path
    {
        const auto home_path =  std::filesystem::path(os::get_home_dir());
        return get_config_path() / SDLK_TEMPLATE_DIRECTORY;
    }

    auto sdlk_engine_conf::is_valid(const std::filesystem::path& file_conf_path) -> bool
    {
        if (!std::filesystem::exists(file_conf_path))
            return false;

        try
        {
            auto j = json_io::read(file_conf_path);
            if (!j.is_object())
            {
                return false;
            }

            if (!j.contains("version") || !j["version"].is_string())
            {
                return false;
            }

            if (!j.contains("last_project_paths") || !j["last_project_paths"].is_array())
            {
                return false;
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    auto sdlk_engine_conf::load_or_init() -> sdlk_engine_conf*
    {
        const auto path = get_file_path();
        static sdlk_engine_conf conf;

        if (is_valid(path))
        {
            auto j = json_io::read(path);

            conf.m_version = j.value("version", SDLK_VERSION);
            conf.m_last_project_paths =
                j["last_project_paths"].get<std::vector<std::string>>();

            return &conf;
        }

        conf.save();
        return &conf;
    }

    auto sdlk_engine_conf::save() const -> void
    {
        const auto path = get_file_path();
        std::filesystem::create_directories(path.parent_path());

        json j;
        j["version"] = m_version;
        j["last_project_paths"] = m_last_project_paths;

        json_io::write(path, j);
    }

    auto sdlk_engine_conf::add_recent_project(const std::string& path) -> void
    {
        m_last_project_paths.erase(std::remove(m_last_project_paths.begin(), m_last_project_paths.end(), path),m_last_project_paths.end());
        m_last_project_paths.insert(m_last_project_paths.begin(), path);

        if (m_last_project_paths.size() > MAX_RECENTS)
        {
            m_last_project_paths.resize(MAX_RECENTS);
        }

        save();
    }

    auto sdlk_engine_conf::get_last_project_paths() const -> std::vector<std::string>
    {
        return m_last_project_paths;
    }
}
