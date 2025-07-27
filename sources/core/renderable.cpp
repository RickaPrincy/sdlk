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

	auto renderable::scale(float pixel_scale) -> void
	{
		this->m_transformation.scale(std::move(pixel_scale));
	}

	auto renderable::rotate(float angle_radians) -> void
	{
		this->m_transformation.rotate(std::move(angle_radians));
	}

	auto renderable::add_translate(glm::vec2 offset) -> void
	{
		this->m_transformation.add_translate(std::move(offset));
	}

	auto renderable::add_rotation(float angle_radians) -> void
	{
		this->m_transformation.add_rotation(std::move(angle_radians));
	}

	auto renderable::add_scale(float scale) -> void
	{
		this->m_transformation.add_scale(std::move(scale));
	}

	auto renderable::set_transformation_model(glm::mat4 transformation_model) -> void
	{
		this->m_transformation.set_model(std::move(transformation_model));
	}

	auto renderable::get_scale() -> float
	{
		return this->m_transformation.get_scale();
	}

	auto renderable::get_rotation() -> float
	{
		return this->m_transformation.get_rotation();
	}

	auto renderable::get_translation() -> glm::vec2
	{
		return this->m_transformation.get_translation();
	}

}  // namespace sdlk
