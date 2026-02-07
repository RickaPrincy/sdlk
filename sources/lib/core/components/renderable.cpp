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
}  // namespace sdlk
