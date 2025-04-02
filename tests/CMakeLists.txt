file(
  GLOB_RECURSE TEST_SOURCES
  LIST_DIRECTORIES false
  *.h *.cpp core/*.cpp)
add_executable(${SDLK_TEST_NAME} ${TEST_SOURCES})

target_include_directories(
  ${SDLK_TEST_NAME}
  PRIVATE "${SDLK_SOURCE_DIR}/include"
  PRIVATE "${SDLK_SOURCE_DIR}/external/googletest/include")

target_link_directories(${SDLK_TEST_NAME} PUBLIC ${CMAKE_BINARY_DIR}/lib)

target_link_libraries(
  ${SDLK_TEST_NAME}
  PUBLIC ${SDLK_LIB_NAME}
  PUBLIC gtest)

set_target_properties(${SDLK_TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                   "${CMAKE_BINARY_DIR}/bin")
