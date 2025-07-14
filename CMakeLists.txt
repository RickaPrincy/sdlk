cmake_minimum_required(VERSION 3.18)

project(sdlk_tools VERSION 0.0.3)

# c++ 17 by default
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# SDL2
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Freetype REQUIRED)

# Download git submodule
set(GIT_SUBMODULES
  "external/glm"
  "external/earcut"
)

foreach(submodule IN LISTS GIT_SUBMODULES)
  if(NOT EXISTS "${CMAKE_SOURCE_DIR}/${submodule}/.git")
    message(STATUS "Init ${submodule} ...")
    execute_process(
      COMMAND git submodule update --init --recursive ${submodule}
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      RESULT_VARIABLE res
      OUTPUT_VARIABLE out
      ERROR_VARIABLE err
      OUTPUT_STRIP_TRAILING_WHITESPACE
      ERROR_STRIP_TRAILING_WHITESPACE
    )
    if(NOT res EQUAL 0)
      message(WARNING "Failed to init submodule ${submodule} : ${err}")
    else()
      message(STATUS "Submodule ${submodule} updated.")
    endif()
  else()
    message(STATUS "Submodule ${submodule} already initialized, skipping.")
  endif()
endforeach()

set(SDLK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SDLK_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(SDLK_IS_MAIN_PROJECT ON)
endif()

# target names
set(SDLK_LIB_NAME sdlk)
set(SDLK_LIB_VERSION 0.0.3)
set(SDLK_LIB_VERSION_MAJOR 0)
set(SDLK_VERSION ${PROJECT_VERSION})
set(SDLK_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(SDLK_BUILD_EXAMPLE ON)

# list of options
option(BUILD_SHARED_LIBS "Build rcli as a shared library"
       ${SDLK_IS_MAIN_PROJECT})
option(SDLK_LIB_BUILD "Build sdlk lib" ON)
option(SDLK_LIB_INSTALL "Install sdlk lib" ${SDLK_IS_MAIN_PROJECT})

# configure build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

if(WIN32)
  add_compile_options(WIN32)
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

# clang-format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES "${SDLK_SOURCE_DIR}/sources/*.hpp"
       "${SDLK_SOURCE_DIR}/include/sdlk/*.hpp"
       "${SDLK_SOURCE_DIR}/examples/*.cpp")
  add_custom_target(
    clang-format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format")
else()
  message(
    WARNING "clang-format not found. Clang-format target will not be available."
  )
endif()

# CPack configuration
set(CPACK_PACKAGE_VENDOR "RickaPrincy <rckprincy@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY SDL2 Kit (SDL2 Wrapper))
include(CPack)
