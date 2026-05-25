//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <string>
#include "../utils/json_reader.hpp"
#include "dirty.hpp"

namespace sdlk::engine
{
    struct project: dirty_object
    {
        std::string m_name{};
        std::string m_path{};

        explicit project(const std::string &name, const std::string &path)
        {
            this->m_name = name;
            this->m_path = path;
        }
    };
}
