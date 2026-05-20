//
// Created by ricka on 2026-05-20.
//

#pragma once
#include <string>

class utils
{
public:
    utils() = delete;

    [[nodiscard]] static auto sanitize(const std::string& name, int max_length = 20) -> std::string;
};
