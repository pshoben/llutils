cmake_minimum_required(VERSION 3.1.0)

project(test_llutils VERSION 0.1)

include(GoogleTest)

add_executable (test_llutils test_llutils.cpp)
enable_testing ()
add_test (NAME test_llutils COMMAND test)

