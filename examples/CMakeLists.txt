add_executable(example main.cpp)

target_include_directories(example PRIVATE ${SDLK_SOURCE_DIR}/include)

target_link_directories(example PRIVATE ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(example PUBLIC ${SDLK_LIB_NAME})

set_target_properties(example PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                         "${CMAKE_BINARY_DIR}/bin")

file(COPY ${CMAKE_SOURCE_DIR}/examples/assets DESTINATION ${CMAKE_BINARY_DIR}/bin)
