cmake_minimum_required(VERSION 3.5.0)
project(Sdlk VERSION 0.1.0 LANGUAGES C CXX)

file(GLOB SOURCES "src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME}
    PUBLIC SDL2
    PUBLIC SDL2_image
    PUBLIC SDL2_ttf
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)
install(DIRECTORY src/include/ DESTINATION include/sdl_kit)

#still static
install(FILES FindSdlk.cmake DESTINATION share/cmake-3.27/Modules)