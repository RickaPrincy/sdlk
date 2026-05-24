//
// Created by ricka on 2026-02-04.
//

#pragma once

#include <functional>
#include <sdlk/core/renderable.hpp>

namespace sdlk
{
	class imgui_renderable : public renderable
	{
		std::function<void()> _render;

	public:
		explicit imgui_renderable(const std::function<void()> &render);

		auto render(const std::shared_ptr<gl_program> &program) -> void override;

		static auto make(const std::function<void()> &render) -> std::shared_ptr<imgui_renderable>;
	};
}  // namespace sdlk
