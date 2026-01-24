//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <glad/glad.h>

#include <memory>

namespace sdlk
{
	class gl_vertex_array
	{
	public:
		GLuint m_id{0};
		gl_vertex_array();

		virtual ~gl_vertex_array();

		auto bind() const -> void;
		auto unbind() const -> void;

		auto enable_attrib(GLuint index) -> void;
		auto attrib_pointer(
			GLuint index,
			GLint size,
			GLenum type,
			GLboolean normalized,
			GLsizei stride,
			const void *offset) -> void;

		[[nodiscard]] auto get_id() const ->  GLuint;
		[[nodiscard]] static auto make() -> std::shared_ptr<gl_vertex_array>;
	};
}