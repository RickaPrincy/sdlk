//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <memory>
#include <sdlk/core/gl/gl_buffer.hpp>
#include <sdlk/core/gl/gl_vertex_array.hpp>

namespace sdlk
{
	class geometry
	{
	protected:
		std::unique_ptr<gl_buffer> m_vbo{};
		std::unique_ptr<gl_buffer> m_ebo{};
		std::unique_ptr<gl_vertex_array> m_vao{};
		bool m_is_indexed{ false };

	public:
	    geometry(
	        std::unique_ptr<gl_vertex_array> vao,
            std::unique_ptr<gl_buffer> vbo,
            std::unique_ptr<gl_buffer> ebo);

	    auto bind_vao() const -> void;
	    auto bind_vbo() const -> void;
	    [[nodiscard]] auto get_vbo_id() const -> GLuint;

		auto render() const -> void;
	};
}  // namespace sdlk
