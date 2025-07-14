project(${SDLK_LIB_NAME} VERSION ${SDLK_LIB_VERSION} LANGUAGES CXX)

set(LIB_SOURCES 
  core/events/event_listener.cpp 
  core/events/observer.cpp 
  core/glad.cpp 
  core/quad.cpp
  core/types.cpp
  core/transformation.cpp
  core/opengl_utils.cpp
  core/static_resource.cpp
  core/converter.cpp
  core/camera.cpp
  core/app.cpp 
  core/component.cpp
  core/shape.cpp 
  core/texture.cpp
  core/image_shape.cpp
  core/text_shape.cpp
  core/textured_shape.cpp
  core/freetype_font.cpp
  core/colored_shape.cpp
)

# Create the library
if(BUILD_SHARED_LIBS)
  add_library(${SDLK_LIB_NAME} SHARED ${LIB_SOURCES})
else()
  add_library(${SDLK_LIB_NAME} STATIC ${LIB_SOURCES})
endif()

# Set include directories for the library
target_include_directories(
  ${SDLK_LIB_NAME} PUBLIC $<BUILD_INTERFACE:${SDLK_SOURCE_DIR}/include>)

target_include_directories(
  ${SDLK_LIB_NAME} PUBLIC $<BUILD_INTERFACE:${SDLK_SOURCE_DIR}/external/glm>)
target_include_directories(
  ${SDLK_LIB_NAME} PUBLIC $<BUILD_INTERFACE:${SDLK_SOURCE_DIR}/external/earcut/include>)

target_include_directories(
  ${SDLK_LIB_NAME} PUBLIC ${FREETYPE_INCLUDE_DIRS})

# target_link
target_link_libraries(
  ${SDLK_LIB_NAME}
  PUBLIC SDL2
  PUBLIC SDL2_image
  PUBLIC Freetype::Freetype)

# set properties
set_target_properties(
  ${SDLK_LIB_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
             SOVERSION ${SDLK_LIB_VERSION_MAJOR}
             VERSION ${SDLK_LIB_VERSION})

# lib install configuration
if(SDLK_LIB_INSTALL)
  include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Version.cmake
    VERSION ${SDLK_VERSION}
    COMPATIBILITY SameMajorVersion)

  include(GNUInstallDirs)
  install(DIRECTORY ${SDLK_SOURCE_DIR}/include/${SDLK_LIB_NAME}
          DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

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

  configure_file(${SDLK_SOURCE_DIR}/cmake/${SDLK_LIB_NAME}Config.cmake.in
                 ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Config.cmake @ONLY)
  # Install the Config, ConfigVersion, and custom Find module files
  install(FILES ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Config.cmake
                ${CMAKE_BINARY_DIR}/cmake/${SDLK_LIB_NAME}Version.cmake
          DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${SDLK_LIB_NAME})
endif()
