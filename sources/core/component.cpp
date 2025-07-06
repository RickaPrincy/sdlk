#include <glad/glad.h>

#include <iostream>
#include <mapbox/earcut.hpp>
#include <sdlk/core/component.hpp>
#include <stdexcept>

#include "utils.hpp"

namespace sdlk
{
	component::component(std::vector<glm::vec2> pixel_vertices, component *parent)
		: sdlk::component(std::move(pixel_vertices), parent->_window_size)
	{
		if (!parent)
		{
			throw std::runtime_error("Parent cannot be null");
		}

		this->p_parent = parent;

		if (this->p_parent)
		{
			this->p_parent->append_child(this);
		}
	}

	component::component(std::vector<glm::vec2> pixel_vertices, const glm::vec2 &window_size)
		: p_parent(nullptr),
		  _window_size(window_size)
	{
		auto polygon = pixels_to_polygon_without_ring(pixel_vertices);
		this->m_indices = mapbox::earcut<uint32_t>(polygon);

		this->m_ndc_vertices = pixels_to_ndc(pixel_vertices, window_size);

		glGenVertexArrays(1, &this->m_vao);
		glGenBuffers(1, &this->m_vbo);
		glGenBuffers(1, &this->m_ebo);

		glBindVertexArray(this->m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
		glBufferData(GL_ARRAY_BUFFER,
			this->m_ndc_vertices.size() * sizeof(glm::vec2),
			this->m_ndc_vertices.data(),
			GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			this->m_indices.size() * sizeof(uint32_t),
			this->m_indices.data(),
			GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	auto component::draw() -> void const
	{
		glBindVertexArray(this->m_vao);
		glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	component::~component()
	{
		if (this->m_ebo)
		{
			glDeleteBuffers(1, &m_ebo);
		}

		if (this->m_vbo)
		{
			glDeleteBuffers(1, &m_vbo);
		}

		if (this->m_vao)
		{
			glDeleteVertexArrays(1, &m_vao);
		}

		std::cout << "clean component\n";
	}

	auto component::append_child(component *child) -> void
	{
		child->p_parent = this;
	}
}  // namespace sdlk
