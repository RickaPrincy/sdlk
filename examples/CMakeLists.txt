add_executable(example main.cpp
        ../include/sdlk/core/imgui/imgui_drawer_utils.hpp
        ../include/sdlk/extra/nfd_wrapper.hpp)

target_include_directories(example PRIVATE ${SDLK_SOURCE_DIR}/include)

target_link_directories(example PRIVATE ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(example PUBLIC ${SDLK_LIB_NAME})

set_target_properties(example PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                         "${CMAKE_BINARY_DIR}/bin")

file(COPY ${SDLK_SOURCE_DIR}/examples/resources DESTINATION ${CMAKE_BINARY_DIR}/bin)
