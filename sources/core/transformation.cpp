#include <SDL2/SDL_video.h>

#include <sdlk/core/app.hpp>
#include <sdlk/core/transformation.hpp>

namespace sdlk
{
	auto transformation::translate(glm::vec2 pixel_offset) -> void
	{
		this->m_model = glm::translate(this->m_model, glm::vec3(pixel_offset, 0.0));
	}

	auto transformation::rotate(float angle_radians) -> void
	{
		this->m_model =
			glm::rotate(this->m_model, std::move(angle_radians), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	auto transformation::set_model(glm::mat4 model) -> void
	{
		this->m_model = std::move(model);
	}

	auto transformation::scale(glm::vec2 pixel_scale) -> void
	{
		this->m_model = glm::scale(this->m_model, glm::vec3(pixel_scale, 1.0f));
	}

	auto transformation::load_uniforms(GLuint *shader_program, std::string model_name) const
		-> void const
	{
		auto loc_model = glGetUniformLocation(*shader_program, model_name.c_str());

		if (loc_model != -1)
		{
			glUniformMatrix4fv(loc_model, 1, GL_FALSE, glm::value_ptr(this->m_model));
		}
	}
}  // namespace sdlk
