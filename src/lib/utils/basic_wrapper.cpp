#include <SDL2/SDL_error.h>

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
