#! /bin/bash
git clone -b v0.0.1 https://github.com/RickaPrincy/sdlk.git 
cd sdlk 
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -S .. -B .
sudo make install
cd ../..
rm -rf sdlk 
