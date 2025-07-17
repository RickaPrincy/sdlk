#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>

namespace sdlk
{
	component::component(app *app, renderable *renderable)
		: observer(app->get_event_listener()),
		  m_renderable(renderable)
	{
		app->add_renderable(this);
	}

	component::component(component *parent, renderable *renderable)
		: observer(parent->p_event_listener),
		  m_renderable(renderable)
	{
		parent->append_child(this);
	}

	auto component::render(GLuint *program) -> void
	{
		this->m_renderable->render(program);

		for (const auto &child : this->p_childs)
		{
			child->render(program);
		}
	}

	auto component::append_child(component *child) -> void
	{
		this->p_childs.push_back(child);
	}

	auto component::bind() -> void const
	{
		this->m_renderable->bind();
	}

	auto component::translate(glm::vec2 pixel_offset) -> void
	{
		this->m_renderable->translate(std::move(pixel_offset));
	}

	auto component::scale(glm::vec2 pixel_scale) -> void
	{
		this->m_renderable->scale(std::move(pixel_scale));
	}

	auto component::rotate(float angle_radians) -> void
	{
		this->m_renderable->rotate(std::move(angle_radians));
	}

	auto component::set_transformation_model(glm::mat4 transformation_model) -> void
	{
		this->m_renderable->set_transformation_model(std::move(transformation_model));
	}
}  // namespace sdlk
