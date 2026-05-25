//
// Created by ricka on 2026-05-17.
//

#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

using json = nlohmann::json;

class json_reader {
public:
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

    json_reader() = delete;
};