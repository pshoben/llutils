cmake_minimum_required(VERSION 3.10.0)

project(lls VERSION 0.1)


#set(THREADS_PREFER_PTHREAD_FLAG_ON)
find_package(Threads)

include_directories(/home/root/git/llutils/harness/)

add_executable (echo_server echo_server.c)
add_executable (socket_client socket_client.c)

add_executable (socket_client_non_blocking socket_client_non_blocking.c)
target_link_libraries(socket_client_non_blocking pthread)

add_executable (relay_server relay_server.cpp)
add_dependencies(relay_server config4cpp)
target_link_libraries(relay_server /home/root/git/llutils/third_party/config4cpp/lib/libconfig4cpp.a)

#add_executable (protodump protodump.cpp protodump_main.cpp)
#add_dependencies(protodump config4cpp)
#target_link_libraries(protodump /home/root/git/llutils/third_party/config4cpp/lib/libconfig4cpp.a)

