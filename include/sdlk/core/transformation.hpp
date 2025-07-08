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
		glm::mat4 m_model{ 1.0f };
		glm::mat4 m_view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		glm::mat4 m_projection = glm::ortho(-1.f, 1.f, -1.f, 1.f, 0.1f, 100.f);

	public:
		transformation() = default;

		auto translate(glm::vec2 offset, SDL_Window *window) -> void;

		auto load_uniforms(GLuint shader_program,
			std::string model_name = "model",
			std::string view_name = "view",
			std::string proj_name = "projection") -> void const;
	};
}  // namespace sdlk
