//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>

namespace sdlk
{
	class transform
	{
	protected:
		float m_scale{ 1.0f };
		float m_rotation_degrees{ 0.0f };
		glm::vec3 m_translation{ glm::vec3(0.0f) };
		glm::mat4 m_model{ glm::mat4(1.0f) };

		auto compose() -> void;

	public:
		transform() = default;

		auto set_scale(float scale) -> void;
		auto set_model(const glm::mat4 &model) -> void;
		auto set_translation(glm::vec2 offset) -> void;
		auto set_rotation(float angle_degrees) -> void;

		auto add_scale(float scale) -> void;
		auto add_translation(glm::vec2 offset) -> void;
		auto add_rotation(float angle_degrees) -> void;

		[[nodiscard]] virtual auto get_model() const -> glm::mat4;
		[[nodiscard]] virtual auto get_scale() const -> float;
		[[nodiscard]] virtual auto get_rotation() const -> float;
		[[nodiscard]] virtual auto get_translation() const -> glm::vec3;

		virtual ~transform() = default;
	};
}  // namespace sdlk