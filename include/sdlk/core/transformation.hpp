#pragma once

#include <SDL2/SDL_video.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace sdlk
{
	class transformation
	{
	private:
		glm::mat4 m_model{ glm::mat4(1.0f) };

	public:
		transformation() = default;

		auto translate(glm::vec2 offset) -> void;
		auto scale(glm::vec2 pixel_scale) -> void;
		auto rotate(float angle_radians) -> void;
		auto set_model(glm::mat4 model) -> void;

		auto load_uniforms(GLuint *shader_program, std::string model_name = "model") const
			-> void const;
	};
}  // namespace sdlk
