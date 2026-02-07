set(IMGUI_DIR ${SDLK_SOURCE_DIR}/external/imgui)

set(SDLK_ENGINE_SOURCES
        main.cpp
        types/project.cpp
        views/home/home.cpp
        views/home/draw_project_card.cpp
)

add_executable(${SDLK_ENGINE_NAME} ${SDLK_ENGINE_SOURCES})

file(COPY resources/images DESTINATION ${CMAKE_BINARY_DIR}/bin/resources)

# Set include directories for the library
target_include_directories(
        ${SDLK_ENGINE_NAME} PRIVATE $<BUILD_INTERFACE:${IMGUI_DIR}>)

target_include_directories(${SDLK_ENGINE_NAME} PRIVATE ${SDLK_SOURCE_DIR}/include)

target_link_libraries(${SDLK_ENGINE_NAME} PRIVATE ${SDLK_LIB_NAME})

set_target_properties(${SDLK_ENGINE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (SDLK_ENGINE_INSTALL)
    install(TARGETS ${SDLK_ENGINE_NAME} DESTINATION bin)
endif ()