//
// Created by ricka on 2025-12-30.
//

#include <sdlk/core/multiple_view.hpp>
#include <stdexcept>

namespace sdlk
{
	multiple_view::multiple_view(const std::map<std::string, std::shared_ptr<renderable>>& childs)
		: m_childs(childs)
	{
	}

	auto multiple_view::get_current() const -> std::shared_ptr<renderable>
	{
		return m_current;
	}

	auto multiple_view::switch_to(const std::string& name, std::optional<renderable_context> ctx) -> void
	{
		if (this->m_childs.find(name) == this->m_childs.end())
		{
			throw std::runtime_error("view::switch_to: no view named '" + name + "' found");
		}

	    const auto &to_be_current = this->m_childs[name];

	    if (ctx.has_value())
	    {
	        to_be_current->set_context(ctx.value());
	    }

		this->m_current = to_be_current;
	}

	auto multiple_view::render(const std::shared_ptr<gl_program>& program) -> void
	{
		if (this->m_current)
		{
			this->m_current->render(program);
		}
	}

	auto multiple_view::add_view(const std::string& name, std::shared_ptr<renderable> child) -> void
	{
		this->m_childs.insert(std::make_pair<std::string, std::shared_ptr<renderable>>(
			name.data(), std::move(child)));
	}
}  // namespace sdlk