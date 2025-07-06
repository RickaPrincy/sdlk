#include <glad/glad.h>

#include <iostream>
#include <mapbox/earcut.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>

namespace sdlk
{
	component::component(app &app, sdlk::polygon polygon) : m_polygon(std::move(polygon))
	{
		app.append_child(this);
		this->_init();
	}

	component::component(component *parent, sdlk::polygon polygon)
		: p_parent(parent),
		  m_polygon(std::move(polygon))
	{
		this->_init();
	}

	auto component::_init() -> void
	{
		if (this->p_parent)
		{
			this->p_parent->append_child(this);
		}

		// Triangulation
		auto indices = mapbox::earcut<uint32_t>(this->m_polygon.data());
		this->m_indices_count = static_cast<GLsizei>(indices.size());

		// Convert polygon (point = array<float, 2>) to glm::vec2 ndc
		auto vertices = this->m_polygon.flattened_as_ndc(this->_window_width, this->_window_height);

		glGenVertexArrays(1, &this->m_vao);
		glGenBuffers(1, &this->m_vbo);
		glGenBuffers(1, &this->m_ebo);

		glBindVertexArray(this->m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(uint32_t),
			indices.data(),
			GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	auto component::draw() -> void const
	{
		if (!this->m_indices_count)
		{
			return;
		}

		glBindVertexArray(this->m_vao);
		glDrawElements(GL_TRIANGLES, this->m_indices_count, GL_UNSIGNED_INT, 0);
	}

	auto component::append_child(component *child) -> void
	{
		child->_window_width = this->_window_width;
		child->_window_height = this->_window_height;
		child->p_parent = this;
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
}  // namespace sdlk
