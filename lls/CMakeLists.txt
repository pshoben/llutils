cmake_minimum_required(VERSION 3.10.0)

project(lls VERSION 0.1)

include_directories(/root/llutils/harness/)

add_executable (echo_server echo_server.c)
add_executable (socket_client socket_client.c)

#add_custom_target(
#   config4cpp
#   COMMAND make
#   WORKING_DIRECTORY /root/llutils/third_party/config4cpp/
#)
#include_directories(/root/llutils/third_party/config4cpp/include)

add_executable (relay_server relay_server.cpp)
add_dependencies(relay_server config4cpp)
target_link_libraries(relay_server /root/llutils/third_party/config4cpp/lib/libconfig4cpp.a)

