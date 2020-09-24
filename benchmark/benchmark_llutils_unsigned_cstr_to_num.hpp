#ifndef benchmark_llutils_unsigned_cstr_to_num_hpp
#define benchmark_llutils_unsigned_cstr_to_num_hpp

#include <benchmark/benchmark.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <llutils.hpp>
#include <time.h>
#include <stdlib.h>
#include <cstdint>
#include "llutils_harness_utils.hpp"
#include <math.h>
#include "llutils_benchmark.h"

using namespace llutils;

static const int NUM_SAMPLES = 1; 
// STEP_SIZE   4 

char bench_atoi_samples[NUM_SAMPLES][64];
size_t bench_atoi_sample_lens[NUM_SAMPLES];

#if 0 // set to 1 for validation/unusable benchmark results & set to 0 to run benchmark without validation of results
#define LLUTILS_EXPECT_VALUE(a,b) llutils_expect_value(a,b)
#else
#define LLUTILS_EXPECT_VALUE(a,b)
#endif

static void fill_samples(int num_bits,int max_bits) {
	//srand(time(0));
	int bits = std::min(num_bits,max_bits);
	for(int i = 0 ; i < NUM_SAMPLES; i++ ) {
		uint128_t r = (uint128_t)rand() * (uint128_t)rand(); 
		uint128_t x = (r + (r<<32) + (r<<64) + (r<<96))%(((uint128_t)1) << bits);
	        //unsigned long high = ((uint128_t)x)/((uint128_t)2<<64);
	        //unsigned long low = ((uint128_t)x)%((uint128_t)2<<64);
		uint128_to_cstr( x, bench_atoi_samples[i], true );
		bench_atoi_sample_lens[i] = strlen(bench_atoi_samples[i]);

	}
}

template <typename T>
static void BM_unsigned_cstr_to_num_v1(benchmark::State& state) {
	// can't use strtoul baseline for 128bit nums
	if( std::numeric_limits<T>::digits > std::numeric_limits<unsigned long>::digits ) {
		state.SkipWithError("Skipping values > ULONG_MAX");
		return;
	}
 	fill_samples(state.range(0),std::numeric_limits<T>::digits);
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state) {
			__attribute__((unused))volatile T y = strtoul(bench_atoi_samples[i],0,10); 
			LLUTILS_EXPECT_VALUE(y,bench_atoi_samples[i]);
		}
}

template <typename T>
static void BM_unsigned_cstr_to_num_v2(benchmark::State& state) {
 	fill_samples(state.range(0),std::numeric_limits<T>::digits);
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state) {
			__attribute__((unused))volatile T y = LLUtils<T>::unsigned_cstr_to_num_v2(bench_atoi_samples[i],bench_atoi_sample_lens[i]); 
			LLUTILS_EXPECT_VALUE(y,bench_atoi_samples[i]);
		}
}

template <typename T>
static void BM_unsigned_cstr_to_num_v3(benchmark::State& state) {
 	fill_samples(state.range(0),std::numeric_limits<T>::digits);
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state) {
			__attribute__((unused))volatile T y = LLUtils<T>::unsigned_cstr_to_num_v3(bench_atoi_samples[i],bench_atoi_sample_lens[i]); 
			LLUTILS_EXPECT_VALUE(y,bench_atoi_samples[i]);
		}
}

template <typename T>
static void BM_unsigned_cstr_to_num_v4(benchmark::State& state) {
 	fill_samples(state.range(0),std::numeric_limits<T>::digits);
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state) {
			__attribute__((unused))volatile T y = LLUtils<T>::unsigned_cstr_to_num_v4(bench_atoi_samples[i],bench_atoi_sample_lens[i]); 
			LLUTILS_EXPECT_VALUE(y,bench_atoi_samples[i]);
		}
}

template <typename T>
static void BM_unsigned_cstr_to_num_v5(benchmark::State& state) {
 	fill_samples(state.range(0),std::numeric_limits<T>::digits);
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state) {
			__attribute__((unused))volatile T y = LLUtils<T>::unsigned_cstr_to_num_v5(bench_atoi_samples[i],bench_atoi_sample_lens[i]); 
			LLUTILS_EXPECT_VALUE(y,bench_atoi_samples[i]);
		}
}

template <typename T>
static void BM_unsigned_cstr_to_num_v6(benchmark::State& state) {
 	fill_samples(state.range(0),std::numeric_limits<T>::digits);
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state) {
			__attribute__((unused))volatile T y = LLUtils<T>::unsigned_cstr_to_num_v6(bench_atoi_samples[i],bench_atoi_sample_lens[i]); 
			LLUTILS_EXPECT_VALUE(y,bench_atoi_samples[i]);
		}
}

template <typename T>
static void BM_unsigned_cstr_to_num_v7(benchmark::State& state) {
 	fill_samples(state.range(0),std::numeric_limits<T>::digits);
	for(int i = 0 ; i < NUM_SAMPLES; i++ )
	   	for (auto _ : state) {
			__attribute__((unused))volatile T y = LLUtils<T>::unsigned_cstr_to_num_v7(bench_atoi_samples[i],bench_atoi_sample_lens[i]); 
			LLUTILS_EXPECT_VALUE(y,bench_atoi_samples[i]);
		}
}



#endif
