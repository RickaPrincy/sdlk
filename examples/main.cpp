#include <sdlk/game/game.hpp>

using namespace sdlk::game;

auto main(const int argc, char** argv) -> int
{
	game dota("Dota", 1200, 800);

	return dota.run(argc, argv);
}