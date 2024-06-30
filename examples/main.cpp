#include <sdlk/components/square.hpp>
#include <sdlk/core/window.hpp>
#include <sdlk/sdlk.hpp>

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(500));
	Square square1(Size(250));
	Square square2(Size(50), Position(0, 125));

	square1.append_child(&square2);
	R_Chess.append_child(&square1);
	R_Chess.run();
	return 0;
}
