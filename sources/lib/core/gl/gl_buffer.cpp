//
// Created by ricka on 2025-12-31.
//

#include <sdlk/core/gl/gl_buffer.hpp>

namespace sdlk
{
	gl_buffer::gl_buffer(const GLenum target) : m_target(target)
	{
		glGenBuffers(1, &m_id);
	}

	gl_buffer::~gl_buffer()
	{
		if (m_id)
		{
			glDeleteBuffers(1, &m_id);
		}
	}

	auto gl_buffer::bind() const -> void
	{
		glBindBuffer(m_target, m_id);
	}

	auto gl_buffer::unbind() const -> void
	{
		glBindBuffer(m_target, 0);
	}

	auto gl_buffer::set_data(const void* data,
		const GLenum usage,
		const std::size_t count,
		const std::size_t element_size) -> void
	{
		this->bind();
		this->m_count = count;
		this->m_element_size = element_size;
		glBufferData(
			m_target, static_cast<GLsizeiptr>(this->m_count * this->m_element_size), data, usage);
	}

	auto gl_buffer::id() -> GLuint&
	{
		return m_id;
	}

	auto gl_buffer::get_count() const -> std::size_t
	{
		return this->m_count;
	}
}  // namespace sdlk
