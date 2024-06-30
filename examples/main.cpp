#include <sdlk/components/square.hpp>
#include <sdlk/core/window.hpp>
#include <sdlk/sdlk.hpp>

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(500));
	Square square1(R_Chess.get_window(), Size(250));
	Square square2(&square1, Size(50), Position(0, 125));

	R_Chess.run();
	return 0;
}
