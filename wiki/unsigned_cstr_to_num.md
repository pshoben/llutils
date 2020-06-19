
# Function unsigned_cstr_to_num

Convert an ascii c-string containing an unsigned whole number to a numeric value (short/int/long/uint128_t)

## Versions

| Versions         | Description          
| ----------------- |:--------------------------------------------------------------------------------------------------------:|
| v1 (baseline)     | strtoul |
| v2  | simple loop with multiply ; using pointer access into buffer            |
| v3  | simple loop with multiply ; using index access into buffer             |
| v4  | simple loop with power of 10 lookup ; using index access into buffer    |
| v5  | simple loop with power of 10 lookup ; using pointer access into buffer    |

## Benchmark Results

![Benchmark Results](https://github.com/pshoben/llutils/blob/master/data/BM_unsigned_cstr_to_num.png "Benchmark Results")

## Analysis

Preferred implementation of LLUtils::unsigned_cstr_to_num<T> on the reference architecture is v2 (naive/simple loop).

However, use of perfect forwarding here reduces performace by a factor of 2x or 3x - increasing the cputime v2 from 1-13ns to 3-23ns.

v1 (blue) is the baseline: strtoul
v2 (orange) is at least 3x faster than baseline when input is a 20-decimal digit number. This improves to 20x times faster for input numbers that have fewer digits. 

v3,v4,v5 attempts to reduce data dependency and improve instruction-level parallelism, but no affect currently visible, so more investigation needed here.


## Conclusions

1. Performance depends strongly on number of digits in the input, and on the width of the variable used to store the number.
2. The optimal version changes depending on the workload. There is no version of the function that is optimal for all input data.
3. Instantiating the function using the smallest width that can handle all expected input produces the best performance:
e.g. short integers run faster using the *unsigned short* instantiation than using the *unsigned int* one.
4. Function versions that use a power of ten lookup table are faster for short and int data, but actually slower for long and 128-bit data. It seems that the overhead of using a larger lookup table (with wider data) crosses a threshold at 32 bits and 10 LUT entries. The level of this threshold is likely dependent on architecture.
5. On this build (gcc (GCC) 8.3.1 -O3) - pointer access into the buffer is faster than indexing, for all data widths. This is liable to change with different compiler and compile options.


| data size                                          | best function version       |
| :--------------------------------------------------| :---------------------------------------------------- |
| unsigned short (up to 5 decimal digits)            | version 5 - simple loop with power of 10 lookup ; using pointer access into buffer  |
| unsigned int (up to 10 decimal digits)             | version 5 - simple loop with power of 10 lookup ; using pointer access into buffer  |
| unsigned long (up to 20 decimal digits)            | version 2 - simple loop with multiply ; using pointer access into buffer |
| unsigned __int128 (greater than 20 decimal digits) | version 3 - simple loop with multiply ; using index access into buffer |


## results

|function version       | RMS                  | Big O                      |
|:----------------------|---------------------:|:--------------------------:|
| version 5 - simple loop with power of 10 lookup ; using pointer access into buffer  | | |
| **BM_unsigned_cstr_to_num_v5<unsigned_short>_RMS** | 35 | **1.38** (1) |
| **BM_unsigned_cstr_to_num_v5<unsigned_int>_RMS** | 51 | **2.13** (1) |
| BM_unsigned_cstr_to_num_v5<unsigned_long>_RMS | 58 | 7.17 (1) |
| BM_unsigned_cstr_to_num_v5<uint128_t>_RMS | 61 | 26.52 (1) |
| | | |
| version 2 - simple loop with multiply ; using pointer access into buffer | | |
| BM_unsigned_cstr_to_num_v2<unsigned_short>_RMS | 45 | 1.98 (1) |
| BM_unsigned_cstr_to_num_v2<unsigned_int>_RMS | 51 | 3.01 (1) |
| **BM_unsigned_cstr_to_num_v2<unsigned_long>_RMS** | 58 | **6.61** (1) |
| BM_unsigned_cstr_to_num_v2<uint128_t>_RMS | 65 | 25.75 (1) |
| | | |
| version 3 - simple loop with multiply ; using index access into buffer  | | |
| BM_unsigned_cstr_to_num_v3<unsigned_short>_RMS | 45 | 2.11 (1) |
| BM_unsigned_cstr_to_num_v3<unsigned_int>_RMS | 51 | 3.12 (1) |
| BM_unsigned_cstr_to_num_v3<unsigned_long>_RMS | 52 | 6.74 (1) |
| **BM_unsigned_cstr_to_num_v3<uint128_t>_RMS** | 65 | **24.55** (1) |
| | | |
| version 4 - simple loop with power of 10 lookup ; using index access into buffer  | | |
| BM_unsigned_cstr_to_num_v4<unsigned_short>_RMS | 31 | 1.60 (1) |
| BM_unsigned_cstr_to_num_v4<unsigned_int>_RMS | 40 | 2.45 (1) |
| BM_unsigned_cstr_to_num_v4<unsigned_long>_RMS | 59 | 8.17 (1) |
| BM_unsigned_cstr_to_num_v4<uint128_t>_RMS | 62 | 27.09 (1) |
| | | |

[Raw Benchmark Results](https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils.txt "Raw Benchmark Results : unsigned_cstr_to_num")



