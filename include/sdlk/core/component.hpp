#pragma once

#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/renderable.hpp>
#include <vector>

namespace sdlk
{
	class component : public observer, public renderable
	{
	protected:
		renderable *p_renderable = nullptr;
		component *p_parent = nullptr;
		std::vector<component *> m_childs{};

		auto append_child(component *child) -> void;

	public:
		component(class app *parent, renderable *);
		component(component *parent, renderable *);

		auto bind() -> void const override;

		auto translate(glm::vec2 pixel_offset) -> void override;
		auto scale(float scale) -> void override;
		auto rotate(float angle_radians) -> void override;
		auto add_translate(glm::vec2 pixel_offset) -> void override;
		auto add_scale(float scale) -> void override;
		auto add_rotation(float angle_radians) -> void override;
		auto set_transformation_model(glm::mat4 transformation_model) -> void override;

		auto render(GLuint *program) -> void override;
	};
}  // namespace sdlk
