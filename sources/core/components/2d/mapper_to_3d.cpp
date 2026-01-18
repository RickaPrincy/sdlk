//
// Created by ricka on 2026-01-18.
//

#include "mapper_to_3d.hpp"

namespace sdlk2d
{
	auto mapper_to_3d::map(const type::polygon& polygon2d)
		-> sdlk3d::type::polygon
	{
		sdlk3d::type::polygon polygon3d;
		polygon3d.reserve(polygon2d.size());

		for (const auto& p : polygon2d)
		{
			polygon3d.emplace_back(p.x, p.y, 0.0f);
		}

		return polygon3d;
	}
}
