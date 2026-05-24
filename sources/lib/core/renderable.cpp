//
// Created by ricka on 2025-12-30.
//

#include <sdlk/core/renderable.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk
{
	auto renderable::render(const std::shared_ptr<gl_program> &program) -> void
	{
		this->m_geometry->render();
	}

	renderable::renderable(std::unique_ptr<geometry> geometry) : m_geometry(std::move(geometry))
	{
	}

    auto renderable::set_context(const renderable_context &context) -> void
    {
        this->m_context = context;
	}

    auto renderable::get_context() -> renderable_context&
    {
        return this->m_context;
    }
}  // namespace sdlk
