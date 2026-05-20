//
// Created by ricka on 2026-05-20.
//

#include "utils.hpp"

auto utils::sanitize(const std::string &name, const int max_length) -> std::string
{
    std::string result;
    result.reserve(name.size());

    for (const char c : name)
    {
        if (std::isalnum(static_cast<unsigned char>(c)))
        {
            result += static_cast<char>(static_cast<unsigned char>(c));
        }
        else if (c == ' ' || c == '-' || c == '_')
        {
            result += '_';
        }
    }

    if (result.size() > static_cast<size_t>(max_length))
    {
        result = result.substr(0, max_length);
    }

    return result;
}
