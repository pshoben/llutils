#include <benchmark/benchmark.h>
#include "benchmark_llutils_unsigned_cstr_to_num.hpp"

using namespace llutils;

static const int STEP_SIZE =  4;

// benchmark performance for uint128 data:
//

BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,uint128_t)->DenseRange(0,sizeof(uint128_t)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,uint128_t)->DenseRange(0,sizeof(uint128_t)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,uint128_t)->DenseRange(0,sizeof(uint128_t)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v4,uint128_t)->DenseRange(0,sizeof(uint128_t)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v5,uint128_t)->DenseRange(0,sizeof(uint128_t)*8,STEP_SIZE)->Complexity();

BENCHMARK_MAIN();

