#include <glad/glad.h>

#include <iostream>
#include <sdlk/core/component.hpp>
#include <stdexcept>

#include "utils.hpp"

namespace sdlk
{
	component::component(std::vector<glm::vec2> pixel_vertex, component *parent)
		: sdlk::component(std::move(pixel_vertex), parent->_window_size)
	{
		if (!parent)
		{
			throw std::runtime_error("Parent cannot be null");
		}

		this->p_parent = parent;
	}

	component::component(std::vector<glm::vec2> pixel_vertex, const glm::vec2 &window_size)
		: p_parent(nullptr),
		  _window_size(window_size)
	{
		if (this->p_parent)
		{
			this->p_parent->append_child(this);
		}

		this->m_ndc_vertex = pixels_to_ndc(std::move(pixel_vertex), window_size);

		glGenVertexArrays(1, &this->m_vao);
		glGenBuffers(1, &this->m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER,
			m_ndc_vertex.size() * sizeof(glm::vec2),
			m_ndc_vertex.data(),
			GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	auto component::draw() -> void const
	{
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_ndc_vertex.size()));
		glBindVertexArray(0);
	}

	component::~component()
	{
		glDeleteBuffers(1, &m_vbo);
		glDeleteVertexArrays(1, &m_vao);
		std::cout << "clean component\n";
	}

	auto component::append_child(component *child) -> void
	{
		child->p_parent = this;
	}
}  // namespace sdlk
