#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>

namespace sdlk
{
	component::component(app *app, sdlk::shape *shape)
		: observer(app->get_event_listener()),
		  m_shape(shape)
	{
		app->append_child(this);
	}

	component::component(component *parent, sdlk::shape *shape)
		: observer(parent->p_event_listener),
		  m_shape(shape)
	{
		parent->append_child(this);
	}

	auto component::render(GLuint *program) -> void
	{
		this->m_shape->bind();

		this->m_transformation.load_uniforms(program);

		this->m_shape->render(program);

		for (const auto &child : this->p_childs)
		{
			child->render(program);
		}
	}

	auto component::translate(glm::vec2 pixel_offset) -> void
	{
		this->m_transformation.translate(std::move(pixel_offset));
	}

	auto component::scale(glm::vec2 pixel_scale) -> void
	{
		this->m_transformation.scale(std::move(pixel_scale));
	}

	auto component::rotate(float angle_radians) -> void
	{
		this->m_transformation.rotate(std::move(angle_radians));
	}

	auto component::set_transformation_model(glm::mat4 transformation_model) -> void
	{
		this->m_transformation.set_model(std::move(transformation_model));
	}

	auto component::append_child(component *child) -> void
	{
		this->p_childs.push_back(child);
	}
}  // namespace sdlk
