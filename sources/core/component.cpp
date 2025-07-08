#include <sdlk/core/app.hpp>
#include <sdlk/core/component.hpp>

namespace sdlk
{
	component::component(app *app, sdlk::shape *shape)
		: observer(app->get_event_listener()),
		  p_window(app->p_window),
		  m_shape(shape)
	{
		app->append_child(this);
	}

	component::component(component *parent, sdlk::shape *shape)
		: observer(parent->p_event_listener),
		  p_window(parent->p_window),
		  m_shape(shape)
	{
		parent->append_child(this);
	}

	auto component::render(GLuint *program) -> void
	{
		this->m_shape->bind();
		this->m_transformation.load_uniforms(*program);
		this->m_shape->draw();

		for (const auto &child : this->p_childs)
		{
			child->render(program);
		}
	}

	auto component::translate(glm::vec2 pixel_offset) -> void
	{
		this->m_transformation.translate(std::move(pixel_offset), this->p_window);
	}

	auto component::append_child(component *child) -> void
	{
		this->p_childs.push_back(child);
	}
}  // namespace sdlk
