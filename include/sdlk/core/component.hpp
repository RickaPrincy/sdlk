#pragma once

#include <SDL2/SDL_video.h>

#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/transformation.hpp>
#include <vector>

namespace sdlk
{
	class component : public observer
	{
	protected:
		shape *m_shape;
		component *p_parent = nullptr;
		SDL_Window *p_window = nullptr;
		std::vector<component *> p_childs{};

		transformation m_transformation{};

		auto append_child(component *child) -> void;

	public:
		component(class app *parent, sdlk::shape *shape);
		component(component *parent, sdlk::shape *shape);

		virtual auto render(GLuint *program) -> void;
		virtual auto translate(glm::vec2 pixel_offset) -> void;
	};
}  // namespace sdlk
