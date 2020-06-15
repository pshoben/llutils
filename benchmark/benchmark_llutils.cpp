#include <benchmark/benchmark.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <llutils.hpp>
#include <time.h>
#include <stdlib.h>
#include <cstdint>

#define NUM_SAMPLES 1000
#define STEP_SIZE   8

typedef unsigned __int128 uint128_t;

char bench_atoi_samples[NUM_SAMPLES][64];

static void fill_samples(int num_digits) {
	srand(time(0));
	for(int i = 0 ; i < NUM_SAMPLES; i++ ) {
		sprintf(bench_atoi_samples[i],"%d",rand());
		// truncate after arg digits
		bench_atoi_samples[i][num_digits]=='\0';
	}
}

template <typename T>
static void BM_unsigned_cstr_to_num_v1(benchmark::State& state) {
 	fill_samples(state.range(0));
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state)
			volatile T y = atoi(bench_atoi_samples[i]); 
}
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,unsigned int)->DenseRange(0,sizeof(unsigned int)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,unsigned long)->DenseRange(0,sizeof(unsigned long)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v1,uint128_t)->DenseRange(0,sizeof(uint128_t)*8,STEP_SIZE);

template <typename T>
static void BM_unsigned_cstr_to_num_v2(benchmark::State& state) {
 	fill_samples(state.range(0));
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state)
			volatile T y = strtol(bench_atoi_samples[i],0,10); 
}
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,unsigned int)->DenseRange(0,sizeof(unsigned int)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,unsigned long)->DenseRange(0,sizeof(unsigned long)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v2,uint128_t)->DenseRange(0,sizeof(uint128_t)*8,STEP_SIZE);


template <typename T>
static void BM_unsigned_cstr_to_num_v3(benchmark::State& state) {
 	fill_samples(state.range(0));
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state)
			volatile T y = LLUtils<T>::unsigned_cstr_to_num_v3(bench_atoi_samples[i],state.range(0)); 
}
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,unsigned short)->DenseRange(0,sizeof(unsigned short)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,unsigned int)->DenseRange(0,sizeof(unsigned int)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,unsigned long)->DenseRange(0,sizeof(unsigned long)*8,STEP_SIZE);
BENCHMARK_TEMPLATE(BM_unsigned_cstr_to_num_v3,uint128_t)->DenseRange(0,sizeof(uint128_t)*8,STEP_SIZE);


BENCHMARK_MAIN();

