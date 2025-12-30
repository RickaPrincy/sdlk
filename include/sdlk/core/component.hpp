//
// Created by ricka on 2025-12-30.
//

#pragma once
#include <memory>
#include <vector>
#include <sdlk/core/renderable.hpp>

namespace sdlk
{
	class component: public renderable
	{
	protected:
		std::vector<std::shared_ptr<renderable>> m_childs{};

	public:
		explicit component(std::vector<std::shared_ptr<renderable>> childs={});

		auto add_child(const std::shared_ptr<renderable> &child) -> void;

		auto render() -> void override;

		~component() override = default;
	};
}  // namespace sdlk
