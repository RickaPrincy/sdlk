#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>

#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

void sdlk::throw_if_not_success(int response, std::string message)
{
	if (response != 0)
	{
		throw std::runtime_error(message + " \n-> " + SDL_GetError());
	}
}

bool sdlk::check::is_success(int response)
{
	return response == 0;
}

SDL_Texture *sdlk::load_image(SDL_Renderer *renderer, const std::string path)
{
	SDL_Surface *surface = IMG_Load(path.c_str());
	if (sdlk::check::is_null(surface))
	{
		throw std::runtime_error("Cannot create surface");
	}

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (sdlk::check::is_null(texture))
	{
		throw std::runtime_error("Cannot create texture");
	}

	return texture;
}
