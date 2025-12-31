//
// Created by ricka on 2025-12-31.
//

#include <sdlk/core/geometry.hpp>
#include <utility>

namespace sdlk
{
	geometry::geometry(std::shared_ptr<gl_vertex_array> vao,
		std::shared_ptr<gl_buffer> vbo,
		std::shared_ptr<gl_buffer> ebo)
		: m_vbo(std::move(vbo)),
		  m_ebo(std::move(ebo)),
		  m_vao(std::move(vao))
	{
		this->m_is_indexed = this->m_ebo != nullptr;
	}

	auto geometry::render() const -> void
	{
		this->m_vao->bind();

		if (this->m_is_indexed)
		{
			glDrawElements(GL_TRIANGLES,
				static_cast<GLsizei>(this->m_ebo->get_count()),
				GL_UNSIGNED_INT,
				nullptr);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->m_vbo->get_count()));
		}
	}
}  // namespace sdlk