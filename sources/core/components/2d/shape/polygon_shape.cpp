//
// Created by ricka on 2025-12-31.
//

#include <array>
#include <sdlk/core/components/2d/shape/polygon_shape.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/geometry.hpp>
#include <sdlk/core/gl/gl_program.hpp>
#include <stdexcept>

namespace sdlk2d
{
	static auto map_points_to_polygon(const type::points& points) -> type::polygon;
	static auto map_as_position_only(const type::polygon& polygon) -> std::vector<glm::vec3>;
	static auto map_as_position_and_uv(const type::polygon& polygon)
		-> std::vector<std::array<float, 5>>;
	static auto map_as_position_and_color(const type::polygon& polygon)
		-> std::vector<std::array<float, 7>>;

	polygon_shape::polygon_shape(const type::polygon& polygon)
	{
		this->m_style = shape_style();

		const auto data = map_as_position_and_color(polygon);

		auto vao = std::make_shared<sdlk::gl_vertex_array>();
		auto vbo = std::make_shared<sdlk::gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vbo->bind();

		// Attrib position + color
		vao->enable_attrib(0);	// position
		vao->enable_attrib(1);	// color

		vao->attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]), nullptr);  // position
		vao->attrib_pointer(1,
			4,
			GL_FLOAT,
			GL_FALSE,
			sizeof(data[0]),
			reinterpret_cast<void*>(3 * sizeof(float)));  // color

		vbo->set_data(data.data(), GL_STATIC_DRAW, data.size(), sizeof(data[0]));

		vbo->unbind();
		vao->unbind();

		this->m_geometry = std::make_shared<sdlk::geometry>(vao, vbo, nullptr);
	}

	polygon_shape::polygon_shape(const type::points& points, const SDL_Color& uniform_color)
		: polygon_shape(map_points_to_polygon(points), uniform_color)
	{
	}

	polygon_shape::polygon_shape(const type::polygon& polygon, const SDL_Color& color)
	{
		this->m_style = shape_style(color);
		const auto data = map_as_position_only(polygon);

		auto vao = std::make_shared<sdlk::gl_vertex_array>();
		auto vbo = std::make_shared<sdlk::gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vbo->bind();

		// Attrib position
		vao->enable_attrib(0);													  // position
		vao->attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]), nullptr);  // position
		vbo->set_data(data.data(), GL_STATIC_DRAW, data.size(), sizeof(data[0]));

		vbo->unbind();
		vao->unbind();

		this->m_geometry = std::make_shared<sdlk::geometry>(vao, vbo, nullptr);
	}

	polygon_shape::polygon_shape(const type::polygon& polygon,
		const std::shared_ptr<texture>& texture)
	{
		this->m_style = shape_style(texture);
		const auto data = map_as_position_and_uv(polygon);

		auto vao = std::make_shared<sdlk::gl_vertex_array>();
		auto vbo = std::make_shared<sdlk::gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vbo->bind();

		// Attrib position + UV
		vao->enable_attrib(0);	// position
		vao->enable_attrib(2);	// UV

		vao->attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(data[0]), nullptr);  // position
		vao->attrib_pointer(2,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(data[0]),
			reinterpret_cast<void*>(3 * sizeof(float)));  // UV

		vbo->set_data(data.data(), GL_STATIC_DRAW, data.size(), sizeof(data[0]));  //

		vbo->unbind();
		vao->unbind();

		this->m_geometry = std::make_shared<sdlk::geometry>(vao, vbo, nullptr);
	}

	auto polygon_shape::render(const std::shared_ptr<sdlk::gl_program>& program) -> void
	{
		const auto& uniform = program->get_uniform();

		const auto style_type = this->m_style.m_type;
		uniform->set("u_use_texture", style_type == shape_style::type::texture);
		uniform->set("u_use_vertex_color", style_type == shape_style::type::vertex);

		switch (style_type)
		{
			case shape_style::type::texture:
				this->m_style.m_texture->bind();
				uniform->set("u_texture", 0);
				break;
			case shape_style::type::uniform:
				uniform->set("u_color", this->m_style.m_ndc_uniform_color.value());
				break;
			default: break;
		}

		renderable::render(program);
	}

	static auto map_as_position_only(const type::polygon& polygon) -> std::vector<glm::vec3>
	{
		std::vector<glm::vec3> result;
		result.reserve(polygon.size());

		for (const auto& vertex : polygon)
		{
			result.emplace_back(vertex.m_position.x, vertex.m_position.y, 0.0f);
		}

		return result;
	}

	static auto map_as_position_and_uv(const type::polygon& polygon)
		-> std::vector<std::array<float, 5>>
	{
		std::vector<std::array<float, 5>> result{};
		result.reserve(polygon.size());

		for (const auto& vertex : polygon)
		{
			if (!vertex.m_uv.has_value())
			{
				throw std::runtime_error("Vertex is missing UV for polygon_shape");
			}

			result.push_back(
				{ vertex.m_position.x, vertex.m_position.y, 0.0f, vertex.m_uv->x, vertex.m_uv->y });
		}

		return result;
	}

	static auto map_as_position_and_color(const type::polygon& polygon)
		-> std::vector<std::array<float, 7>>
	{
		std::vector<std::array<float, 7>> result{};
		result.reserve(polygon.size());

		for (const auto& vertex : polygon)
		{
			if (!vertex.m_color.has_value())
			{
				throw std::runtime_error("Vertex is missing Color for polygon_shape");
			}

			const auto ndc_color = sdlk::converter::sdl_color_to_ndc(vertex.m_color.value());

			result.push_back({ vertex.m_position.x,
				vertex.m_position.y,
				0.0f,
				ndc_color.r,
				ndc_color.g,
				ndc_color.b,
				ndc_color.a });
		}

		return result;
	}

	static auto map_points_to_polygon(const type::points& points) -> type::polygon
	{
		type::polygon polygon{};
		polygon.reserve(points.size());
		for (const auto& point : points)
		{
			polygon.emplace_back(type::vertex(point));
		}
		return polygon;
	}
}  // namespace sdlk2d
