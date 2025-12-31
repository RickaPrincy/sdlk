//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <glad/glad.h>
#include <cstddef>

namespace sdlk
{
	class gl_buffer
	{
		GLuint m_id{0};
		GLenum m_target{};
	public:
		explicit gl_buffer(GLenum target);

		virtual ~gl_buffer();

		auto bind() const -> void;
		auto unbind() const -> void;

		auto set_data(const void *data, std::size_t size, GLenum usage) const -> void;

		[[nodiscard]] auto get_id() const -> GLuint;
	};
}  // namespace sdlk
