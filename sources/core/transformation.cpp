#include <SDL2/SDL_video.h>

#include <glm/gtc/type_ptr.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/opengl_utils.hpp>
#include <sdlk/core/transformation.hpp>

namespace sdlk
{
	auto transformation::compose() -> void
	{
		glm::mat4 T = glm::translate(glm::mat4(1.0f), m_translation);
		glm::mat4 R = glm::rotate(glm::mat4(1.0f), m_rotation_radians, glm::vec3(0, 0, 1));
		glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));

		m_model = T * R * S;
	}

	void transformation::translate(glm::vec2 pos)
	{
		this->m_translation = std::move(glm::vec3(std::move(pos), 0.0f));
		this->compose();
	}

	void transformation::rotate(float angle_radians)
	{
		this->m_rotation_radians = std::move(angle_radians);
		this->compose();
	}

	void transformation::scale(float scale)
	{
		this->m_scale = std::move(scale);
		this->compose();
	}

	void transformation::add_translate(glm::vec2 delta)
	{
		this->m_translation += std::move(glm::vec3(std::move(delta), 0.0f));
		this->compose();
	}

	void transformation::add_rotation(float delta_angle)
	{
		this->m_rotation_radians += std::move(delta_angle);
		this->compose();
	}

	void transformation::add_scale(float delta_scale)
	{
		this->m_scale += std::move(delta_scale);

		if (m_scale < 0.01f)
		{
			this->m_scale = 0.01f;	// prevent negative or zero scale
		}

		this->compose();
	}

	auto transformation::set_model(glm::mat4 model) -> void
	{
		this->m_model = std::move(model);
	}

	auto transformation::load_uniforms(GLuint* shader_program, std::string model_name) const
		-> void const
	{
		auto u_model_loc = get_uniform_loc(shader_program, model_name);
		glUniformMatrix4fv(u_model_loc, 1, GL_FALSE, glm::value_ptr(this->m_model));
	}

	auto transformation::get_scale() -> float
	{
		return this->m_scale;
	}

	auto transformation::get_rotation() -> float
	{
		return this->m_rotation_radians;
	}

	auto transformation::get_translation() -> glm::vec2
	{
		return this->m_translation;
	}
}  // namespace sdlk
