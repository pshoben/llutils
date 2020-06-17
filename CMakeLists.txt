cmake_minimum_required(VERSION 3.1.0)

project(llutils VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -fno-omit-frame-pointer")

add_subdirectory(third_party/googletest)
#add_subdirectory(third_party/benchmark)

include_directories(include)

add_subdirectory (test)
add_subdirectory (benchmark)
add_subdirectory (harness)

