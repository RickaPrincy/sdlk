//
// Created by ricka on 2026-05-25.
//

#pragma once

#include "../types/project.hpp"
#include "validator_result.hpp"

namespace sdlk::engine::project_validator
{
    auto validate(const project& p) -> validation_result;
}