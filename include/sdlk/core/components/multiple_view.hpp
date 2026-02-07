//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <map>
#include <memory>
#include <sdlk/core/components/renderable.hpp>

namespace sdlk
{
	class multiple_view : public renderable
	{
	protected:
		std::shared_ptr<renderable> m_current{};
		std::map<std::string, std::shared_ptr<renderable>> m_childs{};

	public:
		explicit multiple_view(
			const std::map<std::string, std::shared_ptr<renderable>> &childs = {});

		[[nodiscard]] auto get_current() const -> std::shared_ptr<renderable>;

		auto switch_to(const std::string &name) -> void;
		auto add_view(const std::string &name, std::shared_ptr<renderable> child) -> void;

		auto render(const std::shared_ptr<gl_program> &program) -> void override;

		~multiple_view() override = default;
	};
}  // namespace sdlk
