cmake_minimum_required(VERSION 3.5.0)

project(sdlk_example)

add_executable(${PROJECT_NAME} main.cpp)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(Sdlk REQUIRED)

target_link_libraries(sdlk_example 
    SDL2
    SDL2_image
    SDL2_ttf
    Sdlk
)