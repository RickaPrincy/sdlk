#pragma once

#include <cstddef>

namespace sdlk
{
	namespace check
	{
		template<typename T>
		bool is_null(T *ptr)
		{
			return ptr == NULL || ptr == nullptr;
		}
	}  // namespace check
}  // namespace sdlk
