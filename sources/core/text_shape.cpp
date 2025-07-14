#include <iostream>
#include <sdlk/core/quad.hpp>
#include <sdlk/core/shape.hpp>

namespace sdlk
{
	text_shape::text_shape(std::string text, std::shared_ptr<freetype_font> font)
		: shape(polygon(), {}, true),
		  m_text(text),
		  m_font(std::move(font))
	{
		glBindVertexArray(this->m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(
			1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glDisableVertexAttribArray(2);	// for color texture

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	auto text_shape::bind() -> void const
	{
		shape::bind();
		glActiveTexture(GL_TEXTURE0);
	}

	auto text_shape::render(GLuint *program) -> void
	{
		auto use_text_rendering_loc = glGetUniformLocation(*program, "u_useTextRendering");
		if (use_text_rendering_loc == -1)
		{
			std::cerr << "Warning: uniform u_useTextRendering not found or optimized out.\n";
		}
		glUniform1i(use_text_rendering_loc, 1);

		auto use_texture_loc = glGetUniformLocation(*program, "u_useTexture");
		if (use_texture_loc == -1)
		{
			std::cerr << "Warning: uniform u_useTexture not found or optimized out.\n";
		}
		glUniform1i(use_texture_loc, 1);

		auto u_texture_loc = glGetUniformLocation(*program, "u_texture");
		if (u_texture_loc == -1)
		{
			std::cerr << "Warning: u_texture not found or optimized out\n";
		}

		glUniform1i(u_texture_loc, 0);	// TODO: handle texture unit$

		std::string::const_iterator c;
		int x = 0;
		int y = this->m_font->get_ascender();

		for (c = this->m_text.begin(); c != this->m_text.end(); c++)
		{
			auto ch = this->m_font->get_character(*c);

			float xpos = x + ch.bearing.x;
			float ypos = y - ch.bearing.y;

			float w = ch.size.x;
			float h = ch.size.y;

			float vertices[6][4] = {
				{ xpos, ypos, 0.0f, 0.0f },			 // top-left
				{ xpos, ypos + h, 0.0f, 1.0f },		 // bottom-left
				{ xpos + w, ypos + h, 1.0f, 1.0f },	 // bottom-right

				{ xpos, ypos, 0.0f, 0.0f },
				{ xpos + w, ypos + h, 1.0f, 1.0f },
				{ xpos + w, ypos, 1.0f, 0.0f }	// top-right
			};
			// render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.texture_id);

			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.advance >> 6);	 // bitshift by 6 to get value in pixels (2^6 = 64)
		}
	}
}  // namespace sdlk
