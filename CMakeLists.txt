cmake_minimum_required(VERSION 3.22)
project(Yadro)

set(CMAKE_CXX_STANDARD             20)
set(CMAKE_MODULE_PATH              "${CMAKE_SOURCE_DIR}/tools/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

add_subdirectory(yadro)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/Catch2)
add_subdirectory(Tests)
add_executable(yadro_app yadro.cpp)
target_link_libraries(yadro_app yadrolib)

