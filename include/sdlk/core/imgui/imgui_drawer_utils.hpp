//
// Created by ricka on 2026-02-06.
//

#pragma once

#include <imgui.h>

#include <functional>
#include <memory>
#include <sdlk/core/gl/gl_texture.hpp>

namespace sdlk::imgui_drawer_utils
{
	auto centered_window(const std::function<ImVec2()> &size_getter,
		const std::function<void()> &renderable) -> void;

	auto spacing(int iteration = 1) -> void;
	auto image(const std::shared_ptr<gl_texture> &texture, const ImVec2 &size) -> void;
}  // namespace sdlk::imgui_drawer_utils
