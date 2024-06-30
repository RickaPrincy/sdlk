#include <iostream>
#include <sdlk/core/window.hpp>
#include <stdexcept>

#include "../utils/check.hpp"

sdlk::Window::Window(std::string title, sdlk::Size size, Uint32 flags) : sdlk::Component(size)
{
	p_sdl_window = SDL_CreateWindow(
		title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.get_width(), size.get_height(), flags);

	if (check::is_null(p_sdl_window))
	{
		throw std::runtime_error("Cannot create SDL Window");
	}
	SDL_SetWindowFullscreen(p_sdl_window, 0);  // default not fullscreen

	p_sdl_renderer = SDL_CreateRenderer(p_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (check::is_null(p_sdl_renderer))
	{
		throw std::runtime_error("Cannot create SDL Renderer");
	}

	p_sdl_texture = SDL_CreateTexture(
		p_sdl_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_size.get_width(), m_size.get_height());
	if (sdlk::check::is_null(p_sdl_texture))
	{
		throw std::runtime_error("Cannot create SDL Texture");
	}
}

void sdlk::Window::render()
{
	Component::render(p_sdl_renderer);
	SDL_RenderPresent(p_sdl_renderer);
}

sdlk::Window::~Window()
{
	std::cout << "destroy window" << std::endl;
	if (!sdlk::check::is_null(p_sdl_renderer))
	{
		SDL_DestroyRenderer(p_sdl_renderer);
	}

	if (!sdlk::check::is_null(p_sdl_window))
	{
		SDL_DestroyWindow(p_sdl_window);
	}
}
