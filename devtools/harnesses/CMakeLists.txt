cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(devtools_harnesses VERSION 0.1)

#include_directories(../pfwriter/)
#include_directories(../pfwriter/csv/)
#
#include_directories(../preformatter/)
#include_directories(../preformatter/fix/)

add_executable (pfwriter_csv_harness pfwriter_csv_harness_main.cpp 
		../pfwriter/pfwriter_impl_common.cpp
		../pfwriter/pfwriter.cpp
		../pfwriter/csv/pfwriter_impl.cpp)


add_executable (preformatter_fix_harness preformatter_fix_harness_main.cpp 
		../preformatter/preformatter.cpp
		../preformatter/fix/preformatter_impl.cpp
		../pfwriter/pfwriter.cpp
		../pfwriter/csv/pfwriter_impl.cpp)



