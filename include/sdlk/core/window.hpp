#pragma once

#include <SDL2/SDL.h>
#include <sdlk/core/box.hpp>
#include <string>

namespace sdlk {

class Window {

private:
  SDL_Renderer *m_sdl_renderer = nullptr;
  SDL_Window *m_sdl_window = nullptr;

public:
  SDL_Renderer *get_sdl_renderer() const;
  SDL_Window *get_sdl_window() const;
  Size get_size() const;

  Window(std::string title, Size size,
         Position position = Position(SDL_WINDOWPOS_CENTERED),
         Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  virtual ~Window();
};

} // namespace sdlk
