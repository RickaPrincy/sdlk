//
// Created by ricka on 2026-05-17.
//

#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <sdlk/sdlkConfig.hpp>

namespace sdlk::engine
{
    class sdlk_engine_conf
    {
        std::string m_version{SDLK_VERSION};
        std::vector<std::string> m_last_project_paths{};
    public:
        static constexpr size_t MAX_RECENTS = 6;

        [[nodiscard]] static auto get_template_path() -> std::filesystem::path;
        [[nodiscard]] static auto get_config_path() -> std::filesystem::path;
        [[nodiscard]] static auto get_file_path() -> std::filesystem::path;
        [[nodiscard]] static auto load_or_init() -> sdlk_engine_conf*;

        auto save() const -> void;
        auto add_recent_project(const std::string& path) -> void;

        [[nodiscard]] auto get_last_project_paths() const -> std::vector<std::string>;
        [[nodiscard]] static auto is_valid(const std::filesystem::path &file_conf_path) -> bool;

        sdlk_engine_conf(const std::string &version, const std::vector<std::string> &last_projects);
        sdlk_engine_conf() = default;
    };
}