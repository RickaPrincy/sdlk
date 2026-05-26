#include <string>
#include <algorithm>
#include <cctype>
#include "../types/project.hpp"
#include "validator_result.hpp"
#include "project_validator.hpp"

#define MIN_WINDOW_SIZE 200

namespace sdlk::engine::project_validator
{
    static auto is_valid_project_name(const std::string& name) -> bool
    {
        if (name.size() < 3 || name.size() > 32)
        {
            return false;
        }

        return std::all_of(name.begin(), name.end(), [](char c) {
            return std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-';
        });
    }

    auto validate(const project& p) -> validation_result
    {
        validation_result result;
        auto add = [&](const std::string& field, const std::string& msg)
        {
            result.m_valid = false;
            result.m_field_errors[field] = msg;
        };

        if (p.m_name.empty())
        {
            add("name", "Required");
        }
        else if (!is_valid_project_name(p.m_name))
        {
            add("name", "3-32 chars, [a-zA-Z0-9_-]");
        }

        if (p.m_version.empty())
        {
            add("version", "Required");
        }

        if (p.m_start_scene.empty())
        {
            add("start_scene", "Required");
        }

        if (p.m_window_size.x < MIN_WINDOW_SIZE || p.m_window_size.y < MIN_WINDOW_SIZE)
        {
            add("window_size", "Must be >= 200");
        }

        return result;
    }
}