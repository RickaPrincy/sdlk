//
// Created by ricka on 2025-12-31.
//

#include <glm/gtc/type_ptr.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/transform.hpp>

namespace sdlk
{
	auto transform::compose() -> void
	{
		const glm::mat4 T = glm::translate(glm::mat4(1.0f), m_translation);
		const glm::mat4 R =
			glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation_degrees), glm::vec3(0, 0, 1));
		const glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));

		m_model = T * R * S;
	}

	auto transform::set_translation(const glm::vec2 offset) -> void
	{
		this->m_translation = glm::vec3(offset, 0.0f);
		this->compose();
	}

	auto transform::set_rotation(const float angle_degrees) -> void
	{
		this->m_rotation_degrees = angle_degrees;
		this->compose();
	}

	auto transform::set_scale(const float scale) -> void
	{
		this->m_scale = scale;
		this->compose();
	}

	auto transform::add_translation(const glm::vec2 offset) -> void
	{
		this->m_translation += glm::vec3(offset, 0.0f);
		this->compose();
	}

	auto transform::add_rotation(const float angle_degrees) -> void
	{
		this->m_rotation_degrees += angle_degrees;
		this->compose();
	}

	auto transform::add_scale(const float scale) -> void
	{
		this->m_scale += scale;

		if (m_scale < 0.01f)
		{
			this->m_scale = 0.01f;	// prevent negative or zero scale
		}

		this->compose();
	}

	auto transform::set_model(const glm::mat4& model) -> void
	{
		this->m_model = model;
	}

	auto transform::get_scale() const -> float
	{
		return this->m_scale;
	}

	auto transform::get_rotation() const -> float
	{
		return this->m_rotation_degrees;
	}

	auto transform::get_translation() const -> glm::vec3
	{
		return this->m_translation;
	}

	auto transform::get_model() const -> glm::mat4
	{
		return this->m_model;
	}
}  // namespace sdlk
