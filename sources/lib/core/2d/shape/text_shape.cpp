//
// Created by ricka on 2026-01-24.
//

#include <glm/vec4.hpp>
#include <iostream>
#include <locale>
#include <sdlk/core/app.hpp>
#include <sdlk/core/2d/shape/text_shape.hpp>
#include <sdlk/core/gl/gl_program.hpp>
#include <utility>

#include "../fonts/msdf_font_impl.hpp"

namespace sdlk2d
{
	text_shape::text_shape(std::u32string text,
		const text_style &text_style,
		const std::shared_ptr<msdf_font> &font)
		: m_style(text_style),
		  m_text(std::move(text)),
		  m_font(font)
	{
		auto vao = std::make_unique<sdlk::gl_vertex_array>();
		auto vbo = std::make_unique<sdlk::gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vbo->bind();

		vao->enable_attrib(0);	// position
		vao->enable_attrib(2);	// uv

		vao->attrib_pointer(0,
			3,
			GL_FLOAT,
			GL_FALSE,
			sizeof(char_vertex),
			reinterpret_cast<void *>(offsetof(char_vertex, m_pos)));

		vao->attrib_pointer(2,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(char_vertex),
			reinterpret_cast<void *>(offsetof(char_vertex, m_uv)));

		this->m_geometry = std::make_unique<sdlk::geometry>(std::move(vao), std::move(vbo), nullptr);

		vbo->unbind();
		vao->unbind();

		this->m_font->get_impl()->load(this->m_text);
		this->update_vertices();
	}

	auto text_shape::render(const std::shared_ptr<sdlk::gl_program> &program) -> void
	{
		this->m_geometry->bind_vao();
		const auto uniform = program->get_uniform();

		uniform->set("u_use_texture", true);
		uniform->set("u_text_rendering", true);
		uniform->set("u_use_vertex_color", false);

		uniform->set("u_px_range", this->m_font->get_impl()->get_conf().m_pixel_range);
		uniform->set("u_color", this->m_style.m_fg_color.ndc());
		uniform->set("u_bg_color", this->m_style.m_bg_color.ndc());

		this->m_font->get_impl()->get_texture()->bind();
		uniform->set("u_texture", 0);

		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertices.size()));
	}

	auto text_shape::update_vertices() -> void
	{
		this->m_geometry->bind_vao();
		this->m_vertices.clear();

		const auto font_metrics = this->m_font->get_impl()->get_metrics();
		const auto scale = this->m_style.m_size / static_cast<float>(font_metrics.emSize);
		glm::vec2 pen{ 0.0f, static_cast<float>(font_metrics.ascenderY) * scale };

		for (const char32_t &c : this->m_text)
		{
			const auto &opt_glyph = this->m_font->get_impl()->get(c);
			if (!opt_glyph.has_value())
				continue;

			const auto glyph = opt_glyph.value().get();
			if (glyph.isWhitespace())
			{
				pen.x += static_cast<float>(glyph.getAdvance()) * scale;
				continue;
			}

			double pl, pb, pr, pt;
			glyph.getQuadPlaneBounds(pl, pb, pr, pt);

			double ul, ub, ur, ut;
			glyph.getQuadAtlasBounds(ul, ub, ur, ut);

			float x0 = pen.x + static_cast<float>(pl) * scale;
			float y0 = pen.y - static_cast<float>(pt) * scale;
			float x1 = pen.x + static_cast<float>(pr) * scale;
			float y1 = pen.y - static_cast<float>(pb) * scale;

			const auto &atlas = this->m_font->get_impl()->get_bitmap();
			float u0 = static_cast<float>(ul) / static_cast<float>(atlas.width);
			float v0 = static_cast<float>(ut) / static_cast<float>(atlas.height);
			float u1 = static_cast<float>(ur) / static_cast<float>(atlas.width);
			float v1 = static_cast<float>(ub) / static_cast<float>(atlas.height);

			m_vertices.push_back({ { x0, y0, 0 }, { u0, v0 } });
			m_vertices.push_back({ { x1, y1, 0 }, { u1, v1 } });
			m_vertices.push_back({ { x1, y0, 0 }, { u1, v0 } });

			m_vertices.push_back({ { x0, y0, 0 }, { u0, v0 } });
			m_vertices.push_back({ { x0, y1, 0 }, { u0, v1 } });
			m_vertices.push_back({ { x1, y1, 0 }, { u1, v1 } });

			pen.x += static_cast<float>(glyph.getAdvance()) * scale;
		}

		this->m_geometry->bind_vbo();
		glBindBuffer(GL_ARRAY_BUFFER, this->m_geometry->get_vbo_id());
		glBufferData(GL_ARRAY_BUFFER,
			static_cast<GLsizei>(m_vertices.size() * sizeof(char_vertex)),
			m_vertices.data(),
			GL_DYNAMIC_DRAW);
	}
}  // namespace sdlk2d
