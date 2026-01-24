//
// Created by ricka on 2026-01-24.
//

#include <sdlk/core/components/2d/shape/text_shape.hpp>
#include <utility>
#include <glm/vec4.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk2d
{

	struct QuadVertex {
		glm::vec3 pos;
		glm::vec2 uv;
	};

	class QuadRenderer {
	public:
		void draw(const std::array<QuadVertex, 6> &quad) const {
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad), quad.data());
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		GLuint vao;
		GLuint vbo;
	};

	text_shape::text_shape(std::string text, const std::shared_ptr<sdlk::msdf_font> &font)
		: m_font(font),
		  m_text(std::move(text))
	{
		auto vao = std::make_shared<sdlk::gl_vertex_array>();
		auto vbo = std::make_shared<sdlk::gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vbo->bind();

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 5, NULL, GL_DYNAMIC_DRAW);

		vao->enable_attrib(0);	// position
		vao->enable_attrib(2);	// uv

		vao->attrib_pointer(0, 3, GL_FLOAT, GL_FALSE,  5 * sizeof(float), nullptr);  // position
		vao->attrib_pointer(2, 2, GL_FLOAT, GL_FALSE,  5 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));  // uv

		this->m_geometry = std::make_shared<sdlk::geometry>(vao, vbo, nullptr);

		vbo->unbind();
		vao->unbind();
	}

	auto text_shape::render(const std::shared_ptr<sdlk::gl_program> &program) -> void
	{
		const auto uniform = program->get_uniform();

		uniform->set("u_use_texture", true);
		uniform->set("u_text_rendering", true);
		uniform->set("u_use_vertex_color", false);
		uniform->set("u_color", glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

		this->m_font->get_texture()->bind();
		uniform->set("u_texture", 0);

		glm::vec2 pen{0.0, 0.0};
		static float scale = 0.2;

		QuadRenderer quad_renderer{.vao=this->m_geometry->get_vao()->m_id, .vbo=this->m_geometry->get_vbo()->m_id};
		for (const auto &c: this->m_text)
		{
			const auto &glyph = this->m_font->get(c);
			double pl, pb, pr, pt;
			glyph.getQuadPlaneBounds(pl, pb, pr, pt);

			double ul, ub, ur, ut;
			glyph.getQuadAtlasBounds(ul, ub, ur, ut);

			// Transforme plane bounds en positions écran
			float x0 = pen.x + float(pl) * scale;
			float y0 = pen.y + float(pb) * scale;
			float x1 = pen.x + float(pr) * scale;
			float y1 = pen.y + float(pt) * scale;

			// Normalise les UV par la taille de l’atlas
			const auto &atlas = this->m_font->get_bitmap();
			float u0 = float(ul) / float(atlas.width);
			float v0 = float(ub) / float(atlas.height);
			float u1 = float(ur) / float(atlas.width);
			float v1 = float(ut) / float(atlas.height);

			std::array<QuadVertex, 6> quad = {{
				{{x0, y0, 0}, {u0, v0}},
				{{x1, y0, 0}, {u1, v0}},
				{{x1, y1, 0}, {u1, v1}},

				{{x0, y0, 0}, {u0, v0}},
				{{x1, y1, 0}, {u1, v1}},
				{{x0, y1, 0}, {u0, v1}},
			}};

			quad_renderer.draw(quad);

			pen.x += static_cast<float>(glyph.getAdvance()) * scale;
		}
	}
}  // namespace sdlk2d
