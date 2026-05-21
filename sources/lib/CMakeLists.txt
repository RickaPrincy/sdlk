set(IMGUI_DIR ${SDLK_SOURCE_DIR}/sources/lib/core/imgui)
set(IMGUI_SOURCES
    # backends (SDL2 + OPENGL3)
    ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
)

set(SDLK_GAME_SOURCES
    game/game.cpp
    game/world.cpp
    game/game_view.cpp
    game/scene_manager.cpp
    game/entity_manager.cpp
    game/scenes/game_scene.cpp
    game/systems/movement_system.cpp
)

set(LIB_SOURCES
        ${IMGUI_SOURCES}
        ${EXTRA_SOURCES}
        ${SDLK_GAME_SOURCES}
        ../utils/file.cpp
        core/glad/glad.cpp
        core/gl/gl_program.cpp
        core/gl/gl_shader.cpp
        core/gl/gl_uniform.cpp
        core/gl/gl_buffer.cpp
        core/gl/gl_vertex_array.cpp
        core/gl/gl_texture.cpp
        core/events/event_listener.cpp
        core/events/observer.cpp
        core/components/renderable.cpp
        core/components/component.cpp
        core/components/multiple_view.cpp
        core/components/2d/shape/polygon_shape.cpp
        core/components/2d/shape/rectangle_shape.cpp
        core/components/2d/fonts/free_type_handle_wrapper.cpp
        core/components/2d/fonts/msdf_font.cpp
        core/components/2d/fonts/msdf_font_impl.cpp
        core/components/2d/shape/text_shape.cpp
        core/app.cpp
        core/converter.cpp
        core/geometry.cpp
        core/transform.cpp
        core/camera.cpp
        core/imgui/imgui_wrapper.cpp
        core/imgui/imgui_renderable.cpp
        core/imgui/imgui_drawer_utils.cpp
)

# Create the library
if (BUILD_SHARED_LIBS)
    add_library(${SDLK_LIB_NAME} SHARED ${LIB_SOURCES})
else ()
    add_library(${SDLK_LIB_NAME} STATIC ${LIB_SOURCES})
endif ()

file(COPY core/shaders DESTINATION ${CMAKE_BINARY_DIR}/bin/resources)

# Set include directories for the library
target_include_directories(
        ${SDLK_LIB_NAME} PRIVATE $<BUILD_INTERFACE:${IMGUI_DIR}>)

target_include_directories(${SDLK_LIB_NAME} PRIVATE $<BUILD_INTERFACE:${EARCUT_HPP_INCLUDE_DIRS})

target_include_directories(
        ${SDLK_LIB_NAME} PUBLIC $<BUILD_INTERFACE:${SDLK_SOURCE_DIR}/include>)

# target_link
target_link_libraries(${SDLK_LIB_NAME}
        PUBLIC
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_link_libraries(${SDLK_LIB_NAME} PRIVATE Freetype::Freetype)
target_link_libraries(${SDLK_LIB_NAME} PRIVATE msdf-atlas-gen::msdf-atlas-gen)

target_link_libraries(${SDLK_LIB_NAME} PUBLIC imgui::imgui)
target_link_libraries(${SDLK_LIB_NAME} PUBLIC glm::glm-header-only)
target_link_libraries(${SDLK_LIB_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(${SDLK_LIB_NAME} PUBLIC $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)

# set properties
set_target_properties(
        ${SDLK_LIB_NAME}
        PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        SOVERSION ${SDLK_LIB_VERSION_MAJOR}
        VERSION ${SDLK_LIB_VERSION})

# lib install configuration
#if (SDLK_LIB_INSTALL)
    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Version.cmake
            VERSION ${SDLK_VERSION}
            COMPATIBILITY SameMajorVersion)

    include(GNUInstallDirs)
    install(DIRECTORY ${SDLK_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    install(
            TARGETS ${SDLK_LIB_NAME}
            EXPORT ${SDLK_LIB_NAME}Targets
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development)

    # Install the Config and ConfigVersion files
    install(
            EXPORT ${SDLK_LIB_NAME}Targets
            FILE ${SDLK_LIB_NAME}Targets.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${SDLK_LIB_NAME})

    # Configure the Config file
    configure_package_config_file(
            ${SDLK_SOURCE_DIR}/cmake/${SDLK_LIB_NAME}Config.cmake.in
            ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Config.cmake
            INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${SDLK_LIB_NAME}
            PATH_VARS SDLK_SOURCE_DIR
    )

    configure_file(${SDLK_SOURCE_DIR}/cmake/${SDLK_LIB_NAME}Config.cmake.in
            ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Config.cmake @ONLY)

    # Install the Config, ConfigVersion, and custom Find module files
    install(FILES ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Config.cmake
            ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Version.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${SDLK_LIB_NAME})

#endif ()
