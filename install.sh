#! /bin/bash
git clone -b v0.0.4 https://github.com/RickaPrincy/sdlk 
cd sdlk 
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
sudo make install
cd ../..
rm -rf sdlk 
