cmake_minimum_required(VERSION 3.10.0)

project(lls VERSION 0.1)

include_directories(/root/llutils/harness/)

add_executable (echo_server echo_server.c)

add_executable (socket_client socket_client.c)


