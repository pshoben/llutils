cmake_minimum_required(VERSION 3.10.0)

project(benchmark_llutils VERSION 0.1)

add_subdirectory(/root/llutils/third_party/benchmark REQUIRED)
include_directories(/root/llutils/third_party/benchmark/include)

add_executable (benchmark_llutils benchmark_llutils.cpp)
target_link_libraries(benchmark_llutils benchmark::benchmark)

