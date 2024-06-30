#include <sdlk/core/window.hpp>
#include <sdlk/utils/check.hpp>
#include <stdexcept>

sdlk::Size sdlk::Window::get_size() const
{
	int width = 0, height = 0;
	if (!sdlk::check::is_null(m_sdl_window))
	{
		SDL_GetWindowSize(m_sdl_window, &width, &height);
	}
	return Size(width, height);
}

sdlk::Window::Window(std::string title, sdlk::Size size, sdlk::Position position, Uint32 flags)
{
	m_sdl_window =
		SDL_CreateWindow(title.c_str(), position.get_x(), position.get_y(), size.get_width(), size.get_height(), flags);

	if (check::is_null(m_sdl_window))
	{
		throw std::runtime_error("Cannot create SDL Window");
	}

	m_sdl_renderer = SDL_CreateRenderer(m_sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (check::is_null(m_sdl_renderer))
	{
		throw std::runtime_error("Cannot create SDL Renderer");
	}
}

sdlk::Window::~Window()
{
	if (!sdlk::check::is_null(m_sdl_renderer))
	{
		SDL_DestroyRenderer(m_sdl_renderer);
	}

	if (!sdlk::check::is_null(m_sdl_window))
	{
		SDL_DestroyWindow(m_sdl_window);
	}
}
