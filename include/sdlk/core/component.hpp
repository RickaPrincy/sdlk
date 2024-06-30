#pragma once

#include <SDL2/SDL_events.h>

#include <sdlk/core/renderable.hpp>
#include <vector>

namespace sdlk
{
	class Component : public Renderable
	{
	protected:
		bool m_should_renderer_childs = true;
		Position m_real_position;
		std::vector<Component *> p_childs{};
		Component *p_parent = nullptr;

		virtual void render(SDL_Renderer *renderer) override;
		void active_renderer_childs_state();
		void calc_real_position();

		Component() = default;

	public:
		virtual void append_child(Component *component);
		Component(Component *parent, Size size, Position position = Position(), SDL_Texture *texture = nullptr);
	};
}  // namespace sdlk
