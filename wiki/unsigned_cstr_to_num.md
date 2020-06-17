
# Function unsigned_cstr_to_num

Convert an ascii c-string containing an unsigned whole number to a numeric value (short/int/long/uint128_t)

## Versions

| Versions         | Description           | Notes           |
| ---------------- |:---------------------:| -----------------------------------------------------------------------------------:|
| v1 (atoi)        | baseline              | constant time performance at ~34000 ns, regardless of number of digits in input     |
| v2 (strtol)      | another baseline      | constant time performance at ~34000 ns, regardless of number of digits in input     |
| v3 (simple loop) | initial version       | linear performance, starting at ~6000 ns at <8 digits, up to ~37000 ns at 48 digits |

## Benchmark Results

![Benchmark Results](https://github.com/pshoben/llutils/blob/master/data/BM_unsigned_cstr_to_num.png "Benchmark Results")

[Raw Benchmark Results](https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils.txt "Raw Benchmark Results : unsigned_cstr_to_num")



