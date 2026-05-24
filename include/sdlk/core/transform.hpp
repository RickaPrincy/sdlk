//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace sdlk
{
	class transform
	{
	protected:
		glm::vec3 m_scale{ 1.0f };
		glm::mat4 m_model{ glm::mat4(1.0f) };
		glm::vec3 m_translation{ 0.0f };
		glm::vec3 m_rotation_degrees{ 0.0f };

		auto compose() -> void;

	public:
		transform() = default;
	    transform(const transform&) = default;
	    transform(transform&&) noexcept = default;

	    auto operator=(const transform&) -> transform& = default;
	    auto operator=(transform&&) noexcept -> transform& = default;

		auto set_model(const glm::mat4 &model) -> void;

		auto set_scale(float scale) -> void;
		auto set_scale(const glm::vec3 &scale) -> void;

		auto set_translation(const glm::vec3 &offset) -> void;
		auto set_translation(const glm::vec2 &offset) -> void;

		auto set_rotation(float angle_degrees) -> void;
		auto set_rotation(const glm::vec3 &angle_degrees) -> void;

		auto add_translation(const glm::vec3 &offset) -> void;
	    auto add_translation(const glm::vec2 &offset) -> void;

		auto add_scale(float scale) -> void;
		auto add_scale(const glm::vec3 &scale) -> void;

		auto add_rotation(float angle_degrees) -> void;
	    auto add_rotation(const glm::vec3 &angle_degrees) -> void;

		[[nodiscard]] virtual auto get_model() const -> glm::mat4;
		[[nodiscard]] virtual auto get_scale() const -> glm::vec3;
		[[nodiscard]] virtual auto get_rotation() const -> glm::vec3;
		[[nodiscard]] virtual auto get_translation() const -> glm::vec3;

		virtual ~transform() = default;
	};
}  // namespace sdlk