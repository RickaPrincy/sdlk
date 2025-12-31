//
// Created by ricka on 2025-12-30.
//

#include <sdlk/core/renderable/component.hpp>

namespace sdlk
{
	component::component(std::vector<std::shared_ptr<renderable>> childs): m_childs(std::move(childs))
	{
	}

	auto component::add_child(const std::shared_ptr<renderable> &child) -> void
	{
		this->m_childs.push_back(child);
	}

	auto component::render(const std::shared_ptr<gl_program> &program) -> void
	{
		for (const auto &child : this->m_childs)
		{
			child->render(program);
		}
	}
}  // namespace sdlk