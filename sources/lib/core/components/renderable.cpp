//
// Created by ricka on 2025-12-30.
//

#include <sdlk/core/components/renderable.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk
{
	auto renderable::render(const std::shared_ptr<gl_program> &program) -> void
	{
		if (this->m_geometry)
		{
			this->m_geometry->render();
		}
	}

	renderable::renderable(const std::shared_ptr<geometry> &geometry) : m_geometry(geometry)
	{
	}

    auto renderable::set_context(const std::shared_ptr<renderable_context> &context) -> void
    {
        this->m_context = context;
	}

    auto renderable::get_context() -> std::shared_ptr<renderable_context>
    {
        return this->m_context;
    }
}  // namespace sdlk
