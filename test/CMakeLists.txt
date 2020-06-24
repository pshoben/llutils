cmake_minimum_required(VERSION 3.10.0)

project(test_llutils VERSION 0.1)

include(GoogleTest)
include_directories(/root/llutils/third_party/googletest/googletest/include)

include_directories(/root/llutils/harness)

add_executable (test_llutils test_llutils.cpp)
target_link_libraries(test_llutils gtest_main)

add_executable (test_test test_test.cpp)
target_link_libraries(test_test gtest_main)

enable_testing ()
gtest_add_tests(test_llutils "" test_llutils.cpp)
gtest_add_tests(test_test "" test_test.cpp)

