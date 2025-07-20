#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>

namespace sdlk
{
	component::component(app *app, renderable *renderable)
		: observer(app->get_event_listener()),
		  p_renderable(renderable)
	{
		app->add_renderable(this);
	}

	component::component(component *parent, renderable *renderable)
		: observer(parent->m_event_listener),
		  p_renderable(renderable)
	{
		parent->append_child(this);
	}

	auto component::render(GLuint *program) -> void
	{
		this->p_renderable->render(program);

		for (const auto &child : this->m_childs)
		{
			child->render(program);
		}
	}

	auto component::append_child(component *child) -> void
	{
		this->m_childs.push_back(child);
	}

	auto component::bind() -> void const
	{
		this->p_renderable->bind();
	}

	auto component::translate(glm::vec2 pixel_offset) -> void
	{
		this->p_renderable->translate(std::move(pixel_offset));
	}

	auto component::scale(float scale) -> void
	{
		this->p_renderable->scale(std::move(scale));
	}

	auto component::rotate(float angle_radians) -> void
	{
		this->p_renderable->rotate(std::move(angle_radians));
	}

	auto component::add_translate(glm::vec2 translation) -> void
	{
		this->p_renderable->add_translate(std::move(translation));
	}

	auto component::add_rotation(float angle) -> void
	{
		this->p_renderable->add_rotation(std::move(angle));
	}

	auto component::add_scale(float scale) -> void
	{
		this->p_renderable->add_rotation(std::move(scale));
	}

	auto component::set_transformation_model(glm::mat4 transformation_model) -> void
	{
		this->p_renderable->set_transformation_model(std::move(transformation_model));
	}
}  // namespace sdlk
