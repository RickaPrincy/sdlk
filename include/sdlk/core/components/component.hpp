//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <memory>
#include <sdlk/core/components/renderable.hpp>
#include <sdlk/core/events/observer.hpp>
#include <vector>

namespace sdlk
{
	class component : public renderable, public observer
	{
	protected:
		std::vector<std::shared_ptr<renderable>> m_childs{};

	public:
		explicit component(std::vector<std::shared_ptr<renderable>> childs = {});

		auto add_child(const std::shared_ptr<renderable> &child) -> void;

		auto render(const std::shared_ptr<gl_program> &program) -> void override;

		~component() override = default;
	};
}  // namespace sdlk
