//
// Created by ricka on 2026-05-17.
//

#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

using json = nlohmann::json;
namespace json_io
{
    static auto write(const std::filesystem::path &path, const json &j)  ->void
    {
        std::ofstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open project file for saving");
        }

        file << j.dump(2);
    }

    static auto read(const std::filesystem::path &path) -> json
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            throw std::runtime_error("Cannot open file: " + path.string());
        }

        json j;
        file >> j;

        return j;
    }
}