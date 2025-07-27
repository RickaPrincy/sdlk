#include <glm/gtc/type_ptr.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/camera.hpp>
#include <sdlk/core/opengl_utils.hpp>

namespace sdlk
{
	camera::camera(int width, int height)
	{
		this->update(std::move(width), std::move(height));
	}

	auto camera::get_projection() const -> const glm::mat4&
	{
		return this->m_projection;
	}

	auto camera::get_view() const -> const glm::mat4&
	{
		return this->m_view;
	}

	auto camera::translate(const glm::vec2& delta) -> void
	{
		m_position += delta;
		this->update(app::get_width(), app::get_height());
	}

	auto camera::set_position(const glm::vec2& pos) -> void
	{
		m_position = pos;
		this->update(app::get_width(), app::get_height());
	}

	auto camera::set_zoom(float zoom) -> void
	{
		this->m_zoom = glm::max(zoom, 0.01f);  // Avoid negative/zero zoom
		this->update(app::get_width(), app::get_height());
	}

	auto camera::focus_on(const glm::vec2& target) -> void
	{
		this->set_position(target);
		this->update(app::get_width(), app::get_height());
	}

	auto camera::update(int width, int height) -> void
	{
		this->recalculate(std::move(width), std::move(height));
	}

	auto camera::recalculate(int width, int height) -> void
	{
		float visible_width = width / m_zoom;
		float visible_height = height / m_zoom;

		this->m_projection = glm::ortho(0.0f, visible_width, visible_height, 0.0f, -1.0f, 1.0f);
		this->m_view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_position, 0.0f));
	}

	auto camera::get_zoom() -> float
	{
		return this->m_zoom;
	}

	auto camera::get_position() -> glm::vec2
	{
		return this->m_position;
	}

	auto camera::load_uniforms(GLuint* shader_program,
		std::string view_name,
		std::string proj_name) const -> void const
	{
		auto u_view_loc = get_uniform_loc(shader_program, view_name);
		glUniformMatrix4fv(u_view_loc, 1, GL_FALSE, glm::value_ptr(this->m_view));

		auto u_projection_loc = get_uniform_loc(shader_program, proj_name);
		glUniformMatrix4fv(u_projection_loc, 1, GL_FALSE, glm::value_ptr(this->m_projection));
	}
}  // namespace sdlk
