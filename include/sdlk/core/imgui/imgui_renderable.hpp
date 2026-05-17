//
// Created by ricka on 2026-02-04.
//

#pragma once

#include <functional>
#include <sdlk/core/components/renderable.hpp>

namespace sdlk
{
	class imgui_renderable : public renderable
	{
		std::function<void(renderable*)> _render;

	public:
		explicit imgui_renderable(std::function<void(renderable*)> render);

		auto render(const std::shared_ptr<gl_program> &program) -> void override;

		static auto make(const std::function<void(renderable*)> &render) -> std::shared_ptr<imgui_renderable>;
	};
}  // namespace sdlk
