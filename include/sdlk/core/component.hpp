#pragma once

#include <SDL2/SDL_events.h>

#include <sdlk/core/events/event_listener.hpp>
#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/renderable.hpp>
#include <vector>

namespace sdlk
{
	class Component : public Renderable, public Observer
	{
	protected:
		bool m_should_renderer_childs = true;
		Position m_real_position;
		std::vector<Component *> p_childs{};
		Component *p_parent = nullptr;

		void calc_real_position();
		virtual void render(SDL_Renderer *renderer) override;
		virtual void clean_texture(SDL_Renderer *renderer) = 0;

		Component() = default;

	public:
		virtual void set_x(int x) override;
		virtual void set_y(int x) override;
		virtual void set_position(Position position) override;

		virtual void active_renderer_childs_state();
		virtual void append_child(Component *component);
		Component(Component *parent, Size size, Position position = Position(), SDL_Texture *texture = nullptr);
	};
}  // namespace sdlk
