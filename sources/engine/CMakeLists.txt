set(IMGUI_DIR ${SDLK_SOURCE_DIR}/external/imgui)

set(SDLK_ENGINE_SOURCES
        main.cpp
        theme.cpp
        sdlk_engine_conf.cpp
        utils/os.cpp
        utils/utils.cpp
        utils/imgui_drawer_utils.cpp
        utils/nfd_wrapper.cpp
        views/home/home.cpp
        views/home/draw_project_card.cpp
        views/home/trigger_open_project.cpp
        views/home/trigger_new_project.cpp
        views/home/get_last_projects.cpp
        views/home/draw_home_options.cpp
        views/home/draw_create_project.cpp
        views/project_editor/project_editor.cpp
        views/project_editor/shared_state.cpp
        views/project_editor/draw_top_bar.cpp
        views/project_editor/draw_left_side_bar.cpp
        views/project_editor/draw_view_port.cpp
        views/project_editor/draw_right_side_bar.cpp
        serializer/project_serializer.cpp
        loader/project_loader.cpp
        validator/project_validator.cpp
        views/project_editor/draw_left_project_section.cpp
)

add_executable(${SDLK_ENGINE_NAME} ${SDLK_ENGINE_SOURCES})

file(COPY resources/images DESTINATION ${CMAKE_BINARY_DIR}/bin/resources)

# Set include directories for the library
target_include_directories(
        ${SDLK_ENGINE_NAME} PRIVATE $<BUILD_INTERFACE:${IMGUI_DIR}>)

target_include_directories(${SDLK_ENGINE_NAME} PRIVATE ${SDLK_SOURCE_DIR}/include)

target_link_libraries(${SDLK_ENGINE_NAME} PRIVATE ${SDLK_LIB_NAME})
target_link_libraries(${SDLK_ENGINE_NAME} PRIVATE nfd::nfd)
target_link_libraries(${SDLK_ENGINE_NAME} PRIVATE Templi)

set_target_properties(${SDLK_ENGINE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (SDLK_ENGINE_INSTALL)
    install(TARGETS ${SDLK_ENGINE_NAME} DESTINATION bin)
endif ()