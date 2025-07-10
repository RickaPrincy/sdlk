#include <SDL2/SDL_video.h>

#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/transformation.hpp>

namespace sdlk
{

	auto transformation::translate(glm::vec2 pixel_offset) -> void
	{
		auto ndc_offset = converter::pixel_offset_to_ndc(
			std::move(pixel_offset), app::get_width(), app::get_height());

		this->m_model = glm::translate(m_model, glm::vec3(std::move(ndc_offset), 0.0));
	}

	auto transformation::rotate(float angle_radians) -> void
	{
		this->m_model = glm::rotate(m_model, std::move(angle_radians), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	auto transformation::set_model(glm::mat4 model) -> void
	{
		this->m_model = std::move(model);
	}

	auto transformation::scale(glm::vec2 pixel_scale) -> void
	{
		auto ndc_scale = converter::pixel_scale_to_ndc(
			std::move(pixel_scale), app::get_width(), app::get_height());

		this->m_model = glm::scale(m_model, glm::vec3(std::move(ndc_scale), 1.0f));
	}

	auto transformation::load_uniforms(GLuint shader_program,
		std::string model_name,
		std::string view_name,
		std::string proj_name) -> void const
	{
		auto loc_model = glGetUniformLocation(shader_program, model_name.c_str());
		auto loc_view = glGetUniformLocation(shader_program, view_name.c_str());
		auto loc_proj = glGetUniformLocation(shader_program, proj_name.c_str());

		if (loc_model != -1)
		{
			glUniformMatrix4fv(loc_model, 1, GL_FALSE, glm::value_ptr(m_model));
		}

		if (loc_view != -1)
		{
			glUniformMatrix4fv(loc_view, 1, GL_FALSE, glm::value_ptr(m_view));
		}

		if (loc_proj != -1)
		{
			glUniformMatrix4fv(loc_proj, 1, GL_FALSE, glm::value_ptr(m_projection));
		}
	}
}  // namespace sdlk
