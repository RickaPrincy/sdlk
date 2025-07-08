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

	auto component::render() -> void
	{
		this->m_shape->draw();
	}

	auto component::append_child(component *child) -> void
	{
		this->p_childs.push_back(child);
	}
}  // namespace sdlk
