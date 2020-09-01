cmake_minimum_required(VERSION 3.1.0)

project(llutils VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_C_FLAGS_RELEASE "-g -O3 -DNDEBUG -fno-omit-frame-pointer -Wall -Wextra -Wpedantic --save-temps")
set(CMAKE_CXX_FLAGS_RELEASE "-g -O3 -DNDEBUG -fno-omit-frame-pointer -Wall -Wextra -Wpedantic --save-temps ")

add_subdirectory(third_party/googletest)

# delete me add_subdirectory(third_party/benchmark)
# delete me add_subdirectory(third_party/config4cpp)

add_custom_target(
   config4cpp
   COMMAND make
   WORKING_DIRECTORY /root/llutils/third_party/config4cpp/
)
include_directories(/root/llutils/third_party/config4cpp/include)

include_directories(include)

add_subdirectory (test)
add_subdirectory (benchmark)
add_subdirectory (harness)

add_subdirectory (lls)
add_subdirectory (devtools/protodump)
add_subdirectory (devtools/harnesses)


