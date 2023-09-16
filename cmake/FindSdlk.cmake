find_path(Sdlk_INCLUDE_DIR sdl_kit/sdlk.hpp
    PATHS ${CMAKE_INSTALL_PREFIX}/include
    NO_DEFAULT_PATH
)

find_library(Sdlk_LIBRARY
    NAMES Sdlk
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
    NO_DEFAULT_PATH
)

if(Sdlk_INCLUDE_DIR AND Sdlk_LIBRARY)
    set(Sdlk_FOUND TRUE)
endif()

if(Sdlk_FOUND)
    if(NOT Sdlk_FIND_QUIETLY)
        message(STATUS "Found Sdlk: ${Sdlk_LIBRARY}")
    endif()
else()
    if(Sdlk_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find Sdlk library.")
    endif()
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sdlk
    REQUIRED_VARS Sdlk_LIBRARY Sdlk_INCLUDE_DIR
    VERSION_VAR Sdlk_VERSION
)

add_library(Sdlk::Sdlk UNKNOWN IMPORTED)
set_target_properties(Sdlk::Sdlk PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${Sdlk_INCLUDE_DIR}"
    INTERFACE_LINK_LIBRARIES "${Sdlk_LIBRARY}"
)