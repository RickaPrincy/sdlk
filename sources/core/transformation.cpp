#include <SDL2/SDL_video.h>

#include <sdlk/core/transformation.hpp>

#include "utils.hpp"

namespace sdlk
{
	auto transformation::translate(glm::vec2 pixel_offset, SDL_Window *window) -> void
	{
		int window_width{ 0 }, window_height{ 0 };
		SDL_GetWindowSize(window, &window_width, &window_height);

		auto ndc_offset = pixel_offset_to_ndc(std::move(pixel_offset), window_width, window_height);
		this->m_model = glm::translate(m_model, glm::vec3(std::move(ndc_offset), 0.0));
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
