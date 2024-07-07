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

SDL_Texture *sdlk::create_target_texture(SDL_Renderer *renderer, SDL_Texture *texture, int width, int height)
{
	int texture_width{ 0 }, texture_height{ 0 };
	sdlk::throw_if_not_success(
		SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height), "Cannot get texture size");

	SDL_Texture *new_texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		width <= 0 ? texture_width : width,
		height <= 0 ? texture_height : height);

	SDL_Rect rect = { 0, 0, texture_width, texture_height };
	sdlk::throw_if_not_success(SDL_SetRenderTarget(renderer, new_texture), "Cannot set the target");
	sdlk::throw_if_not_success(SDL_RenderCopy(renderer, texture, nullptr, &rect), "Cannot set the target");
	sdlk::throw_if_not_success(SDL_SetRenderTarget(renderer, nullptr), "Cannot reset the target");
	return new_texture;
}
