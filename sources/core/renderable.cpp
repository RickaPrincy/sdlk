#include <sdlk/core/renderable.hpp>

namespace sdlk
{
	auto renderable::render(GLuint *program) -> void
	{
		this->m_transformation.load_uniforms(program);
	}
	auto renderable::bind() -> void const
	{
		// TODO: nothing here
	}

	auto renderable::translate(glm::vec2 pixel_offset) -> void
	{
		this->m_transformation.translate(std::move(pixel_offset));
	}

	auto renderable::scale(glm::vec2 pixel_scale) -> void
	{
		this->m_transformation.scale(std::move(pixel_scale));
	}

	auto renderable::rotate(float angle_radians) -> void
	{
		this->m_transformation.rotate(std::move(angle_radians));
	}

	auto renderable::set_transformation_model(glm::mat4 transformation_model) -> void
	{
		this->m_transformation.set_model(std::move(transformation_model));
	}

}  // namespace sdlk
