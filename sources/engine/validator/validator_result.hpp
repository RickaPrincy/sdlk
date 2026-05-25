//
// Created by ricka on 2026-05-25.
//

#pragma once

#include <string>
#include <unordered_map>

namespace sdlk::engine
{
    struct validation_result
    {
        bool m_valid{true};
        std::unordered_map<std::string,std::string> m_field_errors;

        [[nodiscard]] auto has_error(const std::string& field) const -> bool
        {
            return m_field_errors.find(field) != m_field_errors.end();
        }

        [[nodiscard]] auto error(const std::string& field) const -> const std::string*
        {
            if (const auto it = m_field_errors.find(field); it != m_field_errors.end())
            {
                return &it->second;
            }

            return nullptr;
        }
    };
}
