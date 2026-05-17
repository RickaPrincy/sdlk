//
// Created by ricka on 2026-02-06.
//

#pragma once

#include <memory>

#include "../../types/project.hpp"
#

namespace sdlk
{
	auto draw_project_card(const std::shared_ptr<project>& project) -> void;
}
