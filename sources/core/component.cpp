#include <algorithm>
#include <sdlk/core/component.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/utils/basic_wrapper.hpp>

sdlk::Component::Component(Component *parent, Size size, Position position)
	: Renderable(size, position)
{
	if (!sdlk::check::is_null(parent))
	{
		parent->append_child(this);
	}
}

void sdlk::Component::do_re_render()
{
	m_do_re_render = true;
	if (!sdlk::check::is_null(p_parent))
	{
		p_parent->do_re_render();
	}
}

void sdlk::Component::render(SDL_Renderer *renderer)
{
	if (m_do_re_render)
	{
		std::for_each(
			p_childs.begin(), p_childs.end(), [&](auto *child) { child->render(renderer); });
	}
	m_do_re_render = false;
}

void sdlk::Component::append_child(sdlk::Component *component)
{
	this->p_childs.push_back(component);
	component->p_parent = this;
	component->p_event_listener = p_event_listener;
	component->calc_real_position();
}

void sdlk::Component::calc_real_position()
{
	if (!sdlk::check::is_null(p_parent))
	{
		m_real_position = Position(p_parent->m_real_position.get_x() + m_position.get_x(),
			p_parent->m_real_position.get_y() + m_position.get_y());
	}
	else
	{
		m_real_position = Position(m_position.get_x(), m_position.get_y());
	}
	std::for_each(
		p_childs.begin(), p_childs.end(), [&](auto *child) { child->calc_real_position(); });
}

void sdlk::Component::set_x(int x)
{
	sdlk::Box::set_x(x);
	this->calc_real_position();
}

void sdlk::Component::set_y(int y)
{
	sdlk::Box::set_y(y);
	this->calc_real_position();
}

void sdlk::Component::set_position(Position position)
{
	sdlk::Box::set_position(position);
	this->calc_real_position();
}
