#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <sdlk/core/gl/gl_program.hpp>

namespace sdlk
{
	class camera
	{
	protected:
		float m_zoom{ 1.0f };
		glm::vec2 m_position{ 0.0f };

		glm::mat4 m_projection{ 1.0f };
		glm::mat4 m_view{ 1.0f };

		auto recalculate(int width, int height) -> void;

	public:
		camera(unsigned int width, unsigned int height);

		[[nodiscard]] auto get_zoom() const -> float;
		[[nodiscard]] auto get_position() const -> glm::vec2;

		auto set_position(const glm::vec2& pos) -> void;
		auto translate(const glm::vec2& delta) -> void;

		auto set_zoom(float zoom) -> void;

		auto focus_on(const glm::vec2& target) -> void;

		auto update(unsigned int width, unsigned int height)
			-> void;  // Must be called after any change

		auto load_uniforms(const std::shared_ptr<gl_program>& program) const -> void;

		[[nodiscard]] auto get_projection() const -> const glm::mat4&;
		[[nodiscard]] auto get_view() const -> const glm::mat4&;
	};
}  // namespace sdlk