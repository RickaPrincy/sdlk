#pragma once

#include <memory>
#include <utility>
#include <stdexcept>

namespace sdlk
{
	template <typename T, typename Deleter>
	std::shared_ptr<T> make_sdl_resource_shared(T* raw_pointer, Deleter&& destructor)
	{
		if (!raw_pointer)
		{
			throw std::runtime_error("make_sdl_resource_shared: null pointer");
		}

		return std::shared_ptr<T>(raw_pointer, [d = std::forward<Deleter>(destructor)](T* ptr) {
			if (ptr) {
				d(ptr);
			}
		});
	}
}
