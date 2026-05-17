//
// Created by ricka on 2026-05-17.
//

#pragma once

#include <string>

class os
{
public:
     os() = delete;
	 [[nodiscard]] static auto get_home_dir() -> std::string;
};
