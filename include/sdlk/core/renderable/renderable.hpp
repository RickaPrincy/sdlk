//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <memory>
#include <sdlk/core/geometry.hpp>
#include <sdlk/core/transform.hpp>
#include <sdlk/core/gl/gl_uniform.hpp>

namespace sdlk
{
	class renderable
	{
	protected:
		std::shared_ptr<geometry> m_geometry{};
		std::shared_ptr<transform> m_transform{std::make_shared<transform>()};

	public:
		renderable() = default;

		explicit renderable(const std::shared_ptr<geometry> &geometry);

		virtual auto render(const std::shared_ptr<gl_program> &program) -> void;

		virtual ~renderable() = default;
	};
}