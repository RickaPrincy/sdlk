//
// Created by ricka on 2026-01-18.
//

#pragma once

#include <sdlk/core/components/3d/type.hpp>
#include <sdlk/core/components/2d/type.hpp>

namespace sdlk2d
{
	class mapper_to_3d
	{
	public:
		static auto map(const type::polygon& polygon2d) -> sdlk3d::type::polygon;
	};
}