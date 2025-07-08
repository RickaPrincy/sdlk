#pragma once

#include <sdlk/core/events/observer.hpp>
#include <sdlk/core/shape.hpp>
#include <vector>

namespace sdlk
{
	class component : public observer
	{
	protected:
		shape *m_shape;
		component *p_parent = nullptr;
		std::vector<component *> p_childs{};

		auto append_child(component *child) -> void;

	public:
		component(class app *parent, sdlk::shape *shape);
		component(component *parent, sdlk::shape *shape);

		virtual auto render() -> void;
	};
}  // namespace sdlk
