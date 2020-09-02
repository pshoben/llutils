#include <benchmark/benchmark.h>
#include "benchmark_llutils_unsigned_cstr_to_num.hpp"

using namespace llutils;

static const int STEP_SIZE =  1;

// benchmark whether storage width impacts performance for unsigned short data:
// templates instantitated at each width, but data limited to unsigned short
//

BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v4,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v5,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v6,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v7,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();

BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,unsigned int)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,unsigned int)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,unsigned int)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v4,unsigned int)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v5,unsigned int)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v6,unsigned int)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v7,unsigned int)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();

BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,unsigned long)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,unsigned long)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,unsigned long)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v4,unsigned long)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v5,unsigned long)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v6,unsigned long)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v7,unsigned long)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();

BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,uint128_t)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,uint128_t)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,uint128_t)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v4,uint128_t)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v5,uint128_t)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v6,uint128_t)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v7,uint128_t)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE)->Complexity();

BENCHMARK_MAIN();

