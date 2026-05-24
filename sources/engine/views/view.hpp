//
// Created by ricka on 2026-02-06.
//

#pragma once

#include <memory>
#include <sdlk/core/component.hpp>

namespace sdlk
{
	auto home() -> std::shared_ptr<component>;
	auto project_editor() -> std::shared_ptr<component>;
}