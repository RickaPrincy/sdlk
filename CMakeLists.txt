cmake_minimum_required(VERSION 3.18)

project(sdlk_tools VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# deps
#find_package(rcli REQUIRED)

set(SDLK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SDLK_IS_MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(SDLK_IS_MAIN_PROJECT ON)
endif()

# target names
set(SDLK_LIB_NAME sdlk)
set(SDLK_LIB_VERSION 0.0.1)
set(SDLK_LIB_VERSION_MAJOR 0)
set(SDLK_VERSION ${PROJECT_VERSION})
set(SDLK_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})

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
endif()

if(SDLK_IS_MAIN_PROJECT)
  configure_file(${SDLK_SOURCE_DIR}/PKGBUILD/lib/PKGBUILD.in
                 ${SDLK_SOURCE_DIR}/PKGBUILD/lib/PKGBUILD @ONLY)

  configure_file(${SDLK_SOURCE_DIR}/release_config/create_release.sh
                 ${SDLK_SOURCE_DIR}/create_release.sh @ONLY)

  configure_file(
    ${SDLK_SOURCE_DIR}/${SDLK_LIB_NAME}Config.hpp.in
    ${SDLK_SOURCE_DIR}/include/${SDLK_LIB_NAME}/${SDLK_LIB_NAME}Config.hpp
    @ONLY)
endif()

add_subdirectory(src)

# # Test configuration
# if(SDLK_TEST)
#   set(SUBMODULES external/googletest)
#   find_package(Git REQUIRED)

#   foreach(submodule ${SUBMODULES})
#     execute_process(
#       COMMAND ${GIT_EXECUTABLE} submodule update --init ${submodule}
#       WORKING_DIRECTORY ${SDLK_SOURCE_DIR}
#       RESULT_VARIABLE GIT_SUBMOD_RESULT)

#     if(NOT GIT_SUBMOD_RESULT EQUAL "0")
#       message(
#         FATAL_ERROR
#           "git submodule update --init  ${submodule} failed with ${GIT_SUBMOD_RESULT}, please checkout submodules"
#       )
#     endif()
#   endforeach()

#   add_subdirectory(external/googletest)
#   add_subdirectory(tests)
# endif()

execute_process(
  COMMAND git --version
  RESULT_VARIABLE GIT_RESULT
  OUTPUT_QUIET)

if(NOT GIT_RESULT EQUAL 0)
  message(FATAL_ERROR "git is required")
endif()

# clang-format configuration
find_program(CLANG_FORMAT_EXECUTABLE NAMES clang-format)
if(CLANG_FORMAT_EXECUTABLE)
  file(GLOB_RECURSE ALL_SOURCE_FILES "${SDLK_SOURCE_DIR}/src/lib/*.cpp"
       "${SDLK_SOURCE_DIR}/src/cli/*.cpp"
       "${SDLK_SOURCE_DIR}/include/sdlk/*.hpp")
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
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    SDL2 Kit (SDL2 Wrapper)
)
include(CPack)
