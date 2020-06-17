
# Function unsigned_cstr_to_num

Convert an ascii c-string containing an unsigned whole number to a numeric value (short/int/long/uint128_t)

## Versions

| Versions         | Description           | Notes           |
| ----------------- |:---------------------:| -----------------------------------------------------------------------------------:|
| v1 (strtoul)      | baseline              | baseline performance at ~20-40 ns up to 64 bits                                     |
| v2 (simple loop)  | simple loop           | performance at 1-13ns up to 64 bits and for 128-bit data 1-25-50ns                  |
| v3 (ILP aware x2) | simple loop           | no improvement on v2                                                                |
| v4 (ILP aware x3) | simple loop           | no improvement on v2                                                                |
| v5 (ILP aware x4) | simple loop           | no improvement on v2                                                                |

## Benchmark Results

![Benchmark Results](https://github.com/pshoben/llutils/blob/master/data/BM_unsigned_cstr_to_num.png "Benchmark Results")

## Analysis

Preferred implementation of LLUtils::unsigned_cstr_to_num<T> on the reference architecture is v2 (naive/simple loop).

However, use of perfect forwarding here reduces performace by a factor of 2x or 3x - increasing the cputime v2 from 1-13ns to 3-23ns.

v1 (blue) is the baseline: strtoul
v2 (orange) is at least 3x faster than baseline when input is a 20-decimal digit number. This improves to 20x times faster for input numbers that have fewer digits. 

v3,v4,v5 attempts to reduce data dependency and improve instruction-level parallelism, but no affect currently visible, so more investigation needed here.

[Raw Benchmark Results](https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils.txt "Raw Benchmark Results : unsigned_cstr_to_num")



