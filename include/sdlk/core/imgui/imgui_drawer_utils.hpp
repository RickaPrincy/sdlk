//
// Created by ricka on 2026-02-06.
//

#pragma once

#include <functional>
#include <memory>
#include <sdlk/core/components/2d/shape/texture.hpp>

#include "imgui.h"

namespace sdlk::imgui_drawer_utils
{
	auto centered_window(const std::function<ImVec2()> &size_getter,
		const std::function<void()> &renderable) -> void;

	auto spacing(int iteration = 1) -> void;
	auto image(const std::shared_ptr<sdlk2d::texture> &texture, const ImVec2 &size) -> void;
}  // namespace sdlk::imgui_drawer_utils
