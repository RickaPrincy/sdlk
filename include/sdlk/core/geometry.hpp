//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <sdlk/core/gl/gl_buffer.hpp>
#include <sdlk/core/gl/gl_vertex_array.hpp>

namespace sdlk
{
	class geometry
	{
	protected:
		std::shared_ptr<gl_buffer> m_vbo{};
		std::shared_ptr<gl_buffer> m_ebo{};
		std::shared_ptr<gl_vertex_array> m_vao{};
		bool m_is_indexed{ false };

	public:
		geometry() = default;
		geometry(std::shared_ptr<gl_vertex_array> vao,
			std::shared_ptr<gl_buffer> vbo,
			std::shared_ptr<gl_buffer> ebo);

		auto render() const -> void;
	};
}  // namespace sdlk
