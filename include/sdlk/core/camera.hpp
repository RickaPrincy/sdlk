#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace sdlk
{
	class camera
	{
	protected:
		float m_zoom{ 1.0f };
		glm::vec2 m_position{ 0.0f };

		glm::mat4 m_projection{ 1.0f };
		glm::mat4 m_view{ 1.0f };

		void recalculate(int width, int height);

	public:
		camera(int width, int height);

		[[nodiscard]] auto get_zoom() -> float;
		[[nodiscard]] auto get_position() -> glm::vec2;

		auto set_position(const glm::vec2& pos) -> void;
		auto translate(const glm::vec2& delta) -> void;

		auto set_zoom(float zoom) -> void;

		auto focus_on(const glm::vec2& target) -> void;

		auto update(int width, int height) -> void;	 // Must be called after any change

		auto load_uniforms(GLuint* shader_program,
			std::string view_name = "view",
			std::string proj_name = "projection") const -> void const;

		[[nodiscard]] auto get_projection() const -> const glm::mat4&;
		[[nodiscard]] auto get_view() const -> const glm::mat4&;
	};
}  // namespace sdlk
