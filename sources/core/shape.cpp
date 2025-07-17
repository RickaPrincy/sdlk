#include <glad/glad.h>

#include <iostream>
#include <mapbox/earcut.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/shape.hpp>

namespace sdlk
{
	shape::shape(polygon polygon, std::vector<uint32_t> indices, bool use_texture)
		: m_polygon(polygon),
		  m_use_texture(std::move(use_texture))
	{
		this->m_indices_count = static_cast<unsigned int>(indices.size());

		glGenVertexArrays(1, &this->m_vao);
		glGenBuffers(1, &this->m_vbo);
		glGenBuffers(1, &this->m_ebo);

		glBindVertexArray(this->m_vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(uint32_t),
			indices.data(),
			GL_STATIC_DRAW);
	}

	auto shape::bind() -> void const
	{
		renderable::bind();
		glBindVertexArray(this->m_vao);
	}

	auto shape::render(GLuint *program) -> void
	{
		renderable::render(program);

		if (!this->m_indices_count)
		{
			return;
		}

		auto use_texture_loc = glGetUniformLocation(*program, "u_useTexture");
		if (use_texture_loc == -1)
		{
			std::cerr << "Warning: uniform u_useTexture not found or optimized out.\n";
		}

		glUniform1i(use_texture_loc, this->m_use_texture ? 1 : 0);
		glDrawElements(GL_TRIANGLES, this->m_indices_count, GL_UNSIGNED_INT, 0);
	}

	shape::~shape()
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
		std::cout << "clean shape\n";
	}
}  // namespace sdlk
