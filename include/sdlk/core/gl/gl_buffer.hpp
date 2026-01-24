//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <glad/glad.h>

#include <cstddef>
#include <memory>

namespace sdlk
{
	class gl_buffer
	{
		GLenum m_target{};
		std::size_t m_count{0};
		std::size_t m_element_size{0};

	public:
		GLuint m_id{0};
		explicit gl_buffer(GLenum target);

		virtual ~gl_buffer();

		auto bind() const -> void;
		auto unbind() const -> void;

		auto set_data(const void *data, GLenum usage,  std::size_t count, std::size_t element_size) -> void;

		[[nodiscard]] static auto make(GLenum target) -> std::shared_ptr<gl_buffer>;

		[[nodiscard]] auto get_id() const -> GLuint;
		[[nodiscard]] auto get_count() const -> std::size_t;
	};
}  // namespace sdlk
