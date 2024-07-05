# Project generated with [Templi](https://github.com/RickaPrincy/Templi)

#sdlk :memo:

SDL2 Kit (SDL2 Wrapper)

# Installation :seedling:

- Archlinux

```bash
yay -Sy sdlk 
```
For the moment, you have to build templi to use it if you use another system (not archlinux)

- Dependancies
    - CMake (Version 3.18 or later)
    - C++ Compiler with C++17 support

- Build manually

```bash
git clone https://github.com/RickaPrincy/sdlk 

cd sdlk 

mkdir build

cd build

cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .

sudo make install
```
#### :warning: If some libs are not found after building manually

Identify the installation path of the missing library. For example, let's assume the library is installed in `/usr/local/lib` (on linux it should be there).

If you are using Linux, add the following code to your `~/.zshrc` or `~/.bashrc` based on what you use (replacing `/usr/local/lib` with the actual installation path):

```bash
export LD_LIBRARY_PATH=/usr/local/lib:\$LD_LIBRARY_PATH
```

# Create tar release to pin on your release
```bash
cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build

# a scripts create_release.sh will be created
chmod +x create_release.sh 
create_release
# a release folder will be created
```

# Example

```c++
#include <iostream>
#include <sdlk/components/image.hpp>
#include <sdlk/components/text.hpp>
#include <sdlk/sdlk.hpp>

#include "sdlk/core/events/types.hpp"

using namespace sdlk;

int main(int argc, char *argv[])
{
	App R_Chess("R_Chess", Size(700, 550));
	Image my_image(R_Chess.get_window(),
		// we can use relative path here
		"/home/ricka/Ricka/project/2024/sdlk/examples/assets/images/image.png",
		Size(500, 150),
		Position(60, 0));

	my_image.add_event_listener(
		sdlk::EventType::KEY_DOWN, [&](const SDL_Event &event) { std::cout << "Key down" << std::endl; });

	auto arial = TTF_OpenFont("/home/ricka/Ricka/project/2024/sdlk/examples/assets/font/arial.ttf", 25);
	Text my_text(R_Chess.get_window(), "Hello world", { 0, 255, 255 }, arial);

	R_Chess.run();
	return 0;
}
```
