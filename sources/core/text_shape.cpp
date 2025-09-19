#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/opengl_utils.hpp>
#include <sdlk/core/quad.hpp>
#include <sdlk/core/shape.hpp>

// Assuming a vertex structure is defined like this:
struct TextVertex {
    glm::vec2 position;
    glm::vec2 texCoord;
};

namespace sdlk {
    text_shape::text_shape(std::string text, std::shared_ptr<msdf_font> font, SDL_Color color)
       : shape(polygon(), {}, { false, true, true }),
         m_font(std::move(font))
    {
       // Set the initial color and text
       set_color(color);
       set_text(text);

       // Setup the VAO and VBO once
       glBindVertexArray(m_vao);
       glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

       // We don't need to know the exact size yet, we'll use glBufferData in set_text
       glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

       glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)0);
       glEnableVertexAttribArray(0);

       glVertexAttribPointer(
          1, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (void*)offsetof(TextVertex, texCoord));
       glEnableVertexAttribArray(1);

       glDisableVertexAttribArray(2); // aColor unused for MSDF path
       glBindBuffer(GL_ARRAY_BUFFER, 0);
       glBindVertexArray(0);
    }

    auto text_shape::bind() -> void const
    {
       shape::bind();
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_2D, this->m_font->texture());
    }

    auto text_shape::set_text(std::string text) -> void
    {
       m_text = std::move(text);
       rebuild_vertices();
    }

    auto text_shape::rebuild_vertices() -> void {
       std::vector<TextVertex> vertices;
       vertices.reserve(m_text.length() * 6);

       float cursorX = 0.0f;
       for (char c : m_text) {
          const auto& glyph = m_font->get(c);

          double l, b, r, t;
          glyph.getQuadPlaneBounds(l, b, r, t);

          double al, ab, ar, at;
          glyph.getQuadAtlasBounds(al, ab, ar, at);

          // Corrected vertices to form a single quad
          // Triangle 1
          vertices.push_back({ glm::vec2(l + cursorX, b), glm::vec2(al, ab) });
          vertices.push_back({ glm::vec2(r + cursorX, b), glm::vec2(ar, ab) });
          vertices.push_back({ glm::vec2(r + cursorX, t), glm::vec2(ar, at) });

          // Triangle 2
          vertices.push_back({ glm::vec2(l + cursorX, b), glm::vec2(al, ab) });
          vertices.push_back({ glm::vec2(r + cursorX, t), glm::vec2(ar, at) });
          vertices.push_back({ glm::vec2(l + cursorX, t), glm::vec2(al, at) });

          // Advance the cursor for the next character
          cursorX += glyph.getAdvance();
       }

       m_vertex_count = vertices.size();

       // Bind and upload the new vertex data
       glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
       glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TextVertex), vertices.data(), GL_DYNAMIC_DRAW);
       glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    auto text_shape::get_text() -> std::string
    {
       return m_text;
    }

	auto text_shape::render(GLuint* program) -> void
    {
    	// setup uniforms de base
    	glUniform1i(get_uniform_loc(program, "uUseVecColor"), 0);
    	glUniform1i(get_uniform_loc(program, "uUseTextRendering"), 1);
    	glUniform1i(get_uniform_loc(program, "uUseTexture"), 1);
    	glUniform1i(get_uniform_loc(program, "uTexture"), 0);

    	// toggle debug mode (⚡ nouveau)
    	glUniform1i(get_uniform_loc(program, "uDebugTexture"), 1);

    	// couleurs
    	glUniform4fv(get_uniform_loc(program, "uFgColor"), 1, m_ndc_color.data());
    	glUniform1f(get_uniform_loc(program, "uPxRange"), 2.0f); // ou récup via m_font->pxRange()

    	// bind texture atlas
    	glActiveTexture(GL_TEXTURE0);
    	glBindTexture(GL_TEXTURE_2D, this->m_font->texture());

    	// bind VAO & draw
    	glBindVertexArray(m_vao);
    	glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);

    	// unbind
    	glBindVertexArray(0);
    	glBindTexture(GL_TEXTURE_2D, 0);
    }
}