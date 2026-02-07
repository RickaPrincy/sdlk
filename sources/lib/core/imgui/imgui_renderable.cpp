//
// Created by ricka on 2026-02-04.
//

#include <sdlk/core/imgui/imgui_renderable.hpp>

namespace sdlk
{
	imgui_renderable::imgui_renderable(std::function<void()> render) : _render(std::move(render))
	{
	}

	auto imgui_renderable::render(const std::shared_ptr<gl_program>& program) -> void
	{
		_render();
	}

	auto imgui_renderable::make(const std::function<void()>& render)
		-> std::shared_ptr<imgui_renderable>
	{
		return std::make_shared<imgui_renderable>(render);
	}
}  // namespace sdlk
