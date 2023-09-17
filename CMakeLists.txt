cmake_minimum_required(VERSION 3.5.0)

project(Sdlk VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/**/*.cpp" "src/*.cpp")
add_library(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

#SDL2
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PUBLIC SDL2
    PUBLIC SDL2_image
    PUBLIC SDL_ttf
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/src/include/
    DESTINATION include/sdl_kit
)

if(CMAKE_SYSTEM MATCHES "Linux")
    set(DEFAULT_CMAKE_MODULE_PATH "/usr/share/cmake/Modules")
elseif(CMAKE_SYSTEM MATCHES "Windows")
    set(DEFAULT_CMAKE_MODULE_PATH "C:/Program Files/CMake/share/cmake/Modules")
elseif(CMAKE_SYSTEM MATCHES "Darwin")
    set(DEFAULT_CMAKE_MODULE_PATH "/usr/local/share/cmake/Modules")
else()
    set(DEFAULT_CMAKE_MODULE_PATH "${CMAKE_ROOT}/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules")
endif()

install(
    FILES
        cmake/FindSdlk.cmake
        cmake/FindSDL2.cmake
        cmake/FindSDL2_ttf.cmake
        cmake/FindSDL2_image.cmake
    DESTINATION
        ${DEFAULT_CMAKE_MODULE_PATH}
)