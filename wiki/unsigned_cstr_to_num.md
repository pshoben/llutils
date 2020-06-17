
# Function unsigned_cstr_to_num

Convert an ascii c-string containing an unsigned whole number to a numeric value (short/int/long/uint128_t)

## Versions

| Versions         | Description           | Notes           |
| ---------------- |:---------------------:| -----------------------------------------------------------------------------------:|
| v1 (strtol)      | baseline              | constant time performance at ~3000 ns/100samples                                    |
| v3 (simple loop) | initial version       | performance degrades linearly with number of bits, exceeding baseline at ~20 bits   |

## Benchmark Results

![Benchmark Results](https://github.com/pshoben/llutils/blob/master/data/BM_unsigned_cstr_to_num.png "Benchmark Results")

[Raw Benchmark Results](https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils.txt "Raw Benchmark Results : unsigned_cstr_to_num")



