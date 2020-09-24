cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(protodump VERSION 0.1)

add_executable (protodump protodump.cpp protodump_main.cpp)
add_dependencies(protodump config4cpp)
target_link_libraries(protodump /home/root/git/llutils/third_party/config4cpp/lib/libconfig4cpp.a)

