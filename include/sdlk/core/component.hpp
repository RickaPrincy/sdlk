#pragma once

#include <SDL2/SDL_video.h>

#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/renderable.hpp>
#include <vector>

namespace sdlk
{
	class component : public observer, public renderable
	{
	protected:
		renderable *m_renderable;
		component *p_parent = nullptr;
		std::vector<component *> p_childs{};

		auto append_child(component *child) -> void;

	public:
		component(class app *parent, renderable *);
		component(component *parent, renderable *);

		virtual auto bind() -> void const override;

		virtual auto translate(glm::vec2 pixel_offset) -> void override;

		virtual auto scale(glm::vec2 pixel_scale) -> void override;

		virtual auto rotate(float angle_radians) -> void override;

		virtual auto set_transformation_model(glm::mat4 transformation_model) -> void override;

		virtual auto render(GLuint *program) -> void override;
	};
}  // namespace sdlk
