//
// Created by ricka on 2026-01-24.
//

#include <glm/vec4.hpp>
#include <locale>
#include <sdlk/core/components/2d/shape/text_shape.hpp>
#include <sdlk/core/gl/gl_program.hpp>
#include <utility>

namespace sdlk2d
{
	struct char_vertex
	{
		glm::vec3 m_pos;
		glm::vec2 m_uv;
	};

	text_shape::text_shape(std::u32string text,
		const text_style &text_style,
		const std::shared_ptr<sdlk::msdf_font> &font)
		: m_text(std::move(text)),
		  m_font(font),
		  m_style(text_style)
	{
		this->m_font->load(this->m_text);
		auto vao = std::make_shared<sdlk::gl_vertex_array>();
		auto vbo = std::make_shared<sdlk::gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vbo->bind();

		glBufferData(GL_ARRAY_BUFFER, sizeof(char_vertex) * 6, nullptr, GL_DYNAMIC_DRAW);

		vao->enable_attrib(0);	// position
		vao->enable_attrib(2);	// uv

		vao->attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);	// position
		vao->attrib_pointer(2,
			2,
			GL_FLOAT,
			GL_FALSE,
			5 * sizeof(float),
			reinterpret_cast<void *>(3 * sizeof(float)));  // uv

		this->m_geometry = std::make_shared<sdlk::geometry>(vao, vbo, nullptr);

		vbo->unbind();
		vao->unbind();
	}

	auto text_shape::render(const std::shared_ptr<sdlk::gl_program> &program) -> void
	{
		this->m_geometry->get_vao()->bind();
		const auto uniform = program->get_uniform();

		uniform->set("u_use_texture", true);
		uniform->set("u_text_rendering", true);
		uniform->set("u_use_vertex_color", false);

		uniform->set("u_px_range", this->m_font->get_conf().m_pixel_range);
		uniform->set("u_color", this->m_style.m_fg_color.ndc());
		uniform->set("u_bg_color", this->m_style.m_bg_color.ndc());

		this->m_font->get_texture()->bind();
		uniform->set("u_texture", 0);

		glm::vec2 pen{ -1.0, 0.0 };
		const float scale = this->m_style.m_size;

		std::vector<char_vertex> vertices{};
		vertices.reserve(m_text.size() * 6);

		for (const char32_t &c : this->m_text)
		{
			const auto &opt_glyph = this->m_font->get(c);
			if (!opt_glyph.has_value())
			{
				continue;
			}

			const auto glyph = opt_glyph.value().get();
			if (glyph.isWhitespace())
			{
				pen.x += static_cast<float>(opt_glyph.value().get().getAdvance()) * scale;
				continue;
			}

			double pl, pb, pr, pt;
			glyph.getQuadPlaneBounds(pl, pb, pr, pt);

			double ul, ub, ur, ut;
			glyph.getQuadAtlasBounds(ul, ub, ur, ut);

			float x0 = pen.x + static_cast<float>(pl) * scale;
			float y0 = pen.y + static_cast<float>(pb) * scale;
			float x1 = pen.x + static_cast<float>(pr) * scale;
			float y1 = pen.y + static_cast<float>(pt) * scale;

			const auto &atlas = this->m_font->get_bitmap();
			float u0 = static_cast<float>(ul) / static_cast<float>(atlas.width);
			float v0 = static_cast<float>(ub) / static_cast<float>(atlas.height);
			float u1 = static_cast<float>(ur) / static_cast<float>(atlas.width);
			float v1 = static_cast<float>(ut) / static_cast<float>(atlas.height);

			vertices.push_back({ { x0, y0, 0 }, { u0, v0 } });
			vertices.push_back({ { x1, y0, 0 }, { u1, v0 } });
			vertices.push_back({ { x1, y1, 0 }, { u1, v1 } });
			vertices.push_back({ { x0, y0, 0 }, { u0, v0 } });
			vertices.push_back({ { x1, y1, 0 }, { u1, v1 } });
			vertices.push_back({ { x0, y1, 0 }, { u0, v1 } });

			pen.x += static_cast<float>(glyph.getAdvance()) * scale;
		}

		glBindBuffer(GL_ARRAY_BUFFER, this->m_geometry->get_vbo()->m_id);
		glBufferData(GL_ARRAY_BUFFER,
			static_cast<GLsizei>(vertices.size() * sizeof(char_vertex)),
			vertices.data(),
			GL_STREAM_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
	}
}  // namespace sdlk2d
