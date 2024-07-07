#pragma once

#include <SDL2/SDL_render.h>

#include <string>

namespace sdlk
{
	void throw_if_not_success(int response, std::string message);
	SDL_Texture *load_image(SDL_Renderer *renderer, const std::string path);
	// -1 if you want the image width and height
	SDL_Texture *create_target_texture(SDL_Renderer *renderer, SDL_Texture *texture, int width = -1, int height = -1);

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
