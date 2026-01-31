#include <glm/gtc/type_ptr.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/camera.hpp>

namespace sdlk
{
	camera::camera(const unsigned int width, const unsigned int height)
	{
		this->update(width, height);
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

	auto camera::set_zoom(const float zoom) -> void
	{
		this->m_zoom = glm::max(zoom, 0.01f);  // Avoid negative/zero zoom
		this->update(app::get_width(), app::get_height());
	}

	auto camera::focus_on(const glm::vec2& target) -> void
	{
		this->set_position(target);
		this->update(app::get_width(), app::get_height());
	}

	auto camera::update(const unsigned int width, const unsigned int height) -> void
	{
		this->recalculate(static_cast<int>(width), static_cast<int>(height));
	}

	auto camera::recalculate(const int width, const int height) -> void
	{
		const float visible_width = static_cast<float>(width) / m_zoom;
		const float visible_height = static_cast<float>(height) / m_zoom;

		this->m_projection = glm::ortho(0.0f, visible_width, visible_height, 0.0f, -1.0f, 1.0f);
		this->m_view = glm::translate(glm::mat4(1.0f), glm::vec3(-m_position, 0.0f));
	}

	auto camera::get_zoom() const -> float
	{
		return this->m_zoom;
	}

	auto camera::get_position() const -> glm::vec2
	{
		return this->m_position;
	}

	auto camera::load_uniforms(const std::shared_ptr<gl_program>& program) const -> void
	{
		const auto& uniform = program->get_uniform();
		uniform->set("u_view", this->m_view);
		uniform->set("u_projection", this->m_projection);
	}
}  // namespace sdlk