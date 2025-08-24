cmake_minimum_required(VERSION 3.18)

project(sdlk_tools VERSION 0.0.4)

# c++ 17 by default
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# SDL2
find_package(Freetype REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_path(EARCUT_HPP_INCLUDE_DIRS "mapbox/earcut.hpp")


set(SDLK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SDLK_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(SDLK_IS_MAIN_PROJECT ON)
endif()

# target names
set(SDLK_LIB_NAME sdlk)
set(SDLK_LIB_VERSION ${PROJECT_VERSION})
set(SDLK_LIB_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(SDLK_VERSION ${PROJECT_VERSION})
set(SDLK_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

# list of options
option(BUILD_SHARED_LIBS "Build rcli as a shared library" ON)
option(SDLK_LIB_BUILD "Build sdlk lib" ON)
option(SDLK_LIB_INSTALL "Install sdlk lib" OFF)
option(SDLK_BUILD_EXAMPLE "Build sdlk example" OFF)

# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(SDLK_TEST OFF)
  set(SDLK_BUILD_EXAMPLE OFF)
endif()

if(SDLK_IS_MAIN_PROJECT)
  configure_file(${SDLK_SOURCE_DIR}/.templates/PKGBUILD.in
                 ${SDLK_SOURCE_DIR}/PKGBUILD @ONLY)

  configure_file(${SDLK_SOURCE_DIR}/.templates/install.sh.in
                 ${SDLK_SOURCE_DIR}/install.sh @ONLY)

  configure_file(${SDLK_SOURCE_DIR}/.templates/create-release.sh.in
                 ${SDLK_SOURCE_DIR}/create-release.sh @ONLY)

  configure_file(
    ${SDLK_SOURCE_DIR}/.templates/${SDLK_LIB_NAME}Config.hpp.in
    ${SDLK_SOURCE_DIR}/include/${SDLK_LIB_NAME}/${SDLK_LIB_NAME}Config.hpp
    @ONLY)
endif()

add_subdirectory(sources)

if(SDLK_BUILD_EXAMPLE)
  add_subdirectory(examples)
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY SDL2 Kit (SDL2 Wrapper))
include(CPack)
