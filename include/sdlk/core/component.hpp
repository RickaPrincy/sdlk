#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <sdlk/core/types.hpp>

namespace sdlk
{
	class component
	{
	private:
		polygon m_polygon{};
		int m_indices_count{};

	protected:
		component *p_parent = nullptr;

		GLuint m_vao{}, m_vbo{}, m_ebo{};

	private:
		int _window_width{}, _window_height{};
		auto _init() -> void;

	public:
		component(class app &parent, sdlk::polygon polygon);
		component(component *parent, sdlk::polygon polygon);

		auto draw() -> void const;
		auto append_child(component *component) -> void;

		~component();
		friend class app;
	};
}  // namespace sdlk
