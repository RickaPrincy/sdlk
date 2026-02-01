set(SDLK_ENGINE_SOURCES main.cpp)

add_executable(${SDLK_ENGINE_NAME})

target_sources(${SDLK_ENGINE_NAME} PRIVATE ${SDLK_ENGINE_SOURCES})

target_include_directories(${SDLK_ENGINE_NAME} PRIVATE ${SDLK_SOURCE_DIR}/include)

target_link_libraries(${SDLK_ENGINE_NAME} PRIVATE ${SDLK_LIB_NAME})

set_target_properties(${SDLK_ENGINE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (SDLK_ENGINE_INSTALL)
    install(TARGETS ${SDLK_ENGINE_NAME} DESTINATION bin)
endif ()