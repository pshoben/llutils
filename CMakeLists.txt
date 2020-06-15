cmake_minimum_required(VERSION 3.1.0)

project(llutils VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config/llutils.h.in llutils.h)

include_directories(include)

add_subdirectory (test)

