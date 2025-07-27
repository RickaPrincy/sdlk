#pragma once

#include <SDL2/SDL_video.h>
#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>
#include <string>

namespace sdlk
{
	class transformation
	{
	private:
		float m_scale{ 1.0f };
		float m_rotation_radians{ 0.0f };
		glm::vec3 m_translation{ glm::vec3(0.0f) };
		glm::mat4 m_model{ glm::mat4(1.0f) };

		auto compose() -> void;

	public:
		transformation() = default;

		auto translate(glm::vec2 offset) -> void;
		auto scale(float scale) -> void;
		auto rotate(float angle_radians) -> void;

		auto add_translate(glm::vec2 offset) -> void;
		auto add_scale(float scale) -> void;
		auto add_rotation(float angle_radians) -> void;

		[[nodiscard]] virtual auto get_scale() -> float;
		[[nodiscard]] virtual auto get_rotation() -> float;
		[[nodiscard]] virtual auto get_translation() -> glm::vec2;

		auto set_model(glm::mat4 model) -> void;

		auto load_uniforms(GLuint *shader_program, std::string model_name = "uModel") const
			-> void const;
	};
}  // namespace sdlk
