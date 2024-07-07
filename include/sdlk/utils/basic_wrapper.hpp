#pragma once

#include <SDL2/SDL_render.h>

#include <string>

namespace sdlk
{
	void throw_if_not_success(int response, std::string message);
	SDL_Texture *load_image(SDL_Renderer *renderer, const std::string path);
	namespace check
	{
		template<typename T>
		bool is_null(T *ptr)
		{
			return ptr == NULL || ptr == nullptr;
		}

		bool is_success(int response);
	}  // namespace check
}  // namespace sdlk
