cmake_minimum_required(VERSION 3.10.0)

project(benchmark_llutils VERSION 0.1)

add_subdirectory(/home/root/git/llutils/third_party/benchmark REQUIRED)
include_directories(/home/root/git/llutils/harness/)
include_directories(/home/root/git/llutils/third_party/benchmark/include)

add_executable (benchmark_llutils benchmark_llutils.cpp)
target_link_libraries(benchmark_llutils benchmark::benchmark)

add_executable (benchmark_llutils_unsigned_cstr_to_num_short 
	benchmark_llutils_unsigned_cstr_to_num_short.cpp
	)
target_link_libraries(benchmark_llutils_unsigned_cstr_to_num_short benchmark::benchmark)

add_executable (benchmark_llutils_unsigned_cstr_to_num_int 
	benchmark_llutils_unsigned_cstr_to_num_int.cpp
	)
target_link_libraries(benchmark_llutils_unsigned_cstr_to_num_int benchmark::benchmark)

add_executable (benchmark_llutils_unsigned_cstr_to_num_long 
	benchmark_llutils_unsigned_cstr_to_num_long.cpp
	)
target_link_libraries(benchmark_llutils_unsigned_cstr_to_num_long benchmark::benchmark)

add_executable (benchmark_llutils_unsigned_cstr_to_num_uint128 
	benchmark_llutils_unsigned_cstr_to_num_uint128.cpp
	)
target_link_libraries(benchmark_llutils_unsigned_cstr_to_num_uint128 benchmark::benchmark)


