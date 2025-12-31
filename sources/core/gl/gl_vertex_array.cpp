//
// Created by ricka on 2025-12-31.
//

#include <sdlk/core/gl/gl_vertex_array.hpp>

namespace sdlk
{
	gl_vertex_array::gl_vertex_array()
	{
		glGenVertexArrays(1, &m_id);
	}

	gl_vertex_array::~gl_vertex_array()
	{
		if (m_id)
		{
			glDeleteVertexArrays(1, &m_id);
		}
	}

	auto gl_vertex_array::bind() const -> void
	{
		glBindVertexArray(m_id);
	}

	auto gl_vertex_array::unbind() const -> void
	{
		glBindVertexArray(0);
	}

	auto gl_vertex_array::enable_attrib(const GLuint index) -> void
	{
		glEnableVertexAttribArray(index);
	}

	auto gl_vertex_array::attrib_pointer(const GLuint index,
		const GLint size,
		const GLenum type,
		const GLboolean normalized,
		const GLsizei stride,
		const void *offset) -> void
	{
		glVertexAttribPointer(index, size, type, normalized, stride, offset);
	}

	auto gl_vertex_array::get_id() const -> GLuint
	{
		return m_id;
	}
}  // namespace sdlk
