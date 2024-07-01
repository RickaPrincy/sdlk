#include <iostream>
#include <sdlk/core/window.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

sdlk::Window::Window(std::string title, sdlk::Size size, Uint32 flags) : sdlk::Component(nullptr, size)
{
	p_sdl_window = SDL_CreateWindow(
		title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.get_width(), size.get_height(), flags);

	if (check::is_null(p_sdl_window))
	{
		throw std::runtime_error("Cannot create SDL Window");
	}
	sdlk::throw_if_not_success(SDL_SetWindowFullscreen(p_sdl_window, 0), "Cannot set false fullscreen mode");

	p_sdl_renderer = SDL_CreateRenderer(p_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (check::is_null(p_sdl_renderer))
	{
		throw std::runtime_error("Cannot create SDL Renderer");
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

void sdlk::Window::clean_texture(SDL_Renderer *renderer)
{
	if (sdlk::check::is_null(p_sdl_texture))
	{
		p_sdl_texture = SDL_CreateTexture(p_sdl_renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			m_size.get_width(),
			m_size.get_height());
	}

	if (sdlk::check::is_null(p_sdl_texture))
	{
		throw std::runtime_error("Cannot create SDL Texture");
	}

	// window texture is just a square which is filled by blank
	if (!sdlk::check::is_success(SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255)) ||
		!sdlk::check::is_success(SDL_SetRenderTarget(renderer, p_sdl_texture)) ||
		!sdlk::check::is_success(SDL_RenderClear(renderer)) ||
		!sdlk::check::is_success(SDL_SetRenderTarget(renderer, NULL)))
	{
		throw std::runtime_error("Texture creation failed for a div");
	}
}
