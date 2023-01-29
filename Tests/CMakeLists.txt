add_executable(test test.cpp)
target_link_libraries(test yadrolib)
message(${CMAKE_SOURCE_DIR})
target_link_libraries(test Catch2::Catch2WithMain)