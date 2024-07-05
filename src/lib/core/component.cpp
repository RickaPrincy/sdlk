#include <algorithm>
#include <sdlk/core/component.hpp>
#include <sdlk/core/events/types.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

sdlk::Component::Component(Component *parent, Size size, Position position, SDL_Texture *texture)
	: Renderable(size, position, texture)
{
	if (!sdlk::check::is_null(parent))
	{
		p_parent = parent;
		p_parent->append_child(this);
	}
}

void sdlk::Component::render(SDL_Renderer *renderer)
{
	if (m_should_renderer_childs)
	{
		this->clean_texture(renderer);
		std::for_each(p_childs.begin(), p_childs.end(), [&](auto *child) { child->render(renderer); });
	}

	if (!sdlk::check::is_null(p_parent) && SDL_SetRenderTarget(renderer, p_parent->p_sdl_texture) != 0)
	{
		throw std::runtime_error("Cannot set the target to the component the parent");
	}

	Renderable::render(renderer);
	sdlk::throw_if_not_success(SDL_SetRenderTarget(renderer, NULL), "Cannot reset render target");

	m_should_renderer_childs = false;
}

void sdlk::Component::active_renderer_childs_state()
{
	m_should_renderer_childs = true;
	if (!sdlk::check::is_null(p_parent))
	{
		p_parent->active_renderer_childs_state();
	}
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
		m_real_position = Position(m_real_position.get_x(), m_real_position.get_y());
	}
	std::for_each(p_childs.begin(), p_childs.end(), [&](auto *child) { child->calc_real_position(); });
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
