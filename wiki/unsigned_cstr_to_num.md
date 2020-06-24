
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

In summary, on the reference architecture, the preferred implementation is v5  - a simple loop with power of 10 lookup ; using pointer access into buffer.

The preferred template instantiation of the function is the narrowest data width able to handle the largest required value, but no narrower than (unsigned int). That is: the unsigned int instantiation outperforms the short instantiation. 

## Unsigned short Data (up to 16 bits):

For unsigned short data, **v5** of the function is fastest. In addition, the (unsigned int) instantiation performs better than the (unsigned short) instantiation on average. 

|function version       | RMS                  | Big O                      |
|:----------------------|---------------------:|:--------------------------:|
| BM_unsigned_cstr_to_num_v1<unsigned_short>_RMS | 8 | 21.15 (1) |
| BM_unsigned_cstr_to_num_v2<unsigned_short>_RMS | 43 | 2.41 (1) |
| BM_unsigned_cstr_to_num_v3<unsigned_short>_RMS | 39 | 2.39 (1) |
| BM_unsigned_cstr_to_num_v4<unsigned_short>_RMS | 31 | 1.51 (1) |
| BM_unsigned_cstr_to_num_v5<unsigned_short>_RMS | 28 | 1.65 (1) |
|----------------------|---------------------|--------------------------|
| BM_unsigned_cstr_to_num_v1<unsigned_int>_RMS | 9 | 22.27 (1) |
| BM_unsigned_cstr_to_num_v2<unsigned_int>_RMS | 56 | 2.07 (1) |
| BM_unsigned_cstr_to_num_v3<unsigned_int>_RMS | 46 | 1.78 (1) |
| BM_unsigned_cstr_to_num_v4<unsigned_int>_RMS | 22 | 1.61 (1) |
| **BM_unsigned_cstr_to_num_v5<unsigned_int>_RMS** | 39 | **1.33** (1) |
|----------------------|---------------------|--------------------------|
| BM_unsigned_cstr_to_num_v1<unsigned_long>_RMS | 8 | 21.45 (1) |
| BM_unsigned_cstr_to_num_v2<unsigned_long>_RMS | 43 | 2.28 (1) |
| BM_unsigned_cstr_to_num_v3<unsigned_long>_RMS | 42 | 1.77 (1) |
| BM_unsigned_cstr_to_num_v4<unsigned_long>_RMS | 41 | 2.37 (1) |
| BM_unsigned_cstr_to_num_v5<unsigned_long>_RMS | 40 | 2.35 (1) |
|----------------------|---------------------|--------------------------|
| BM_unsigned_cstr_to_num_v2<uint128_t>_RMS | 44 | 3.59 (1) |
| BM_unsigned_cstr_to_num_v3<uint128_t>_RMS | 46 | 3.57 (1) |
| BM_unsigned_cstr_to_num_v4<uint128_t>_RMS | 47 | 3.82 (1) |
| BM_unsigned_cstr_to_num_v5<uint128_t>_RMS | 47 | 3.63 (1) |


[Raw Benchmark results (unsigned short)](https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_short.txt)

<table>
  <tr>
    <td width="50%">unsigned short data (up to 16 bits) processed using various template instantiations of the function: unsigned short, unsigned int, unsigned long, unsigned __int128</td>
    <td>Same data, plotted without baseline: </td>
  </tr>
  <tr>
    <td><img src="https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_short.png"  alt="unsigned_cstr_to_num<short>"></td>
    <td><img src="https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_short_ignore_v1.png" alt="unsigned_cstr_to_num<short> (nobaseline)" ></td>
   </tr> 
</table>



## Unsigned int (32-bit) data:

For unsigned int data, **v5** of the function is fastest. In addition, the (unsigned int) instantiation performs better than the wider instantiations on average.

|function version       | RMS                  | Big O                      |
|:----------------------|---------------------:|:--------------------------:|
| BM_unsigned_cstr_to_num_v1<unsigned_int>_RMS | 15 | 24.45 (1) |
| BM_unsigned_cstr_to_num_v2<unsigned_int>_RMS | 50 | 2.97 (1) |
| BM_unsigned_cstr_to_num_v3<unsigned_int>_RMS | 50 | 3.79 (1) |
| BM_unsigned_cstr_to_num_v4<unsigned_int>_RMS | 50 | 2.34 (1) |
| **BM_unsigned_cstr_to_num_v5<unsigned_int>_RMS** | 51 | **2.24** (1) |
|----------------------|---------------------|--------------------------|
| BM_unsigned_cstr_to_num_v1<unsigned_long>_RMS | 15 | 24.49 (1) |
| BM_unsigned_cstr_to_num_v2<unsigned_long>_RMS | 51 | 3.35 (1) |
| BM_unsigned_cstr_to_num_v3<unsigned_long>_RMS | 50 | 3.74 (1) |
| BM_unsigned_cstr_to_num_v4<unsigned_long>_RMS | 48 | 3.92 (1) |
| BM_unsigned_cstr_to_num_v5<unsigned_long>_RMS | 51 | 3.77 (1) |
|----------------------|---------------------|--------------------------|
| BM_unsigned_cstr_to_num_v2<uint128_t>_RMS | 56 | 6.35 (1) |
| BM_unsigned_cstr_to_num_v3<uint128_t>_RMS | 52 | 6.29 (1) |
| BM_unsigned_cstr_to_num_v4<uint128_t>_RMS | 55 | 6.31 (1) |
| BM_unsigned_cstr_to_num_v5<uint128_t>_RMS | 54 | 6.50 (1) |

[Raw Benchmark results (unsigned int)](https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_int.txt)

<table>
  <tr>
    <td width="50%">unsigned int data (up to 32 bits) processed using various template instantiations of the function: unsigned short, unsigned int, unsigned long, unsigned __int128</td>
    <td>Same data, plotted without baseline: </td>
  </tr>
  <tr>
    <td><img src="https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_int.png"  alt="unsigned_cstr_to_num<int>"></td>
    <td><img src="https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_int_ignore_v1.png" alt="unsigned_cstr_to_num<int> (nobaseline)" ></td>
   </tr>
</table>

## unsigned long (64-bit) data:

For unsigned long data, **v5** of the function is fastest. In addition, the (unsigned long) instantiation performs better than the wider instantiation on average.

|function version       | RMS                  | Big O                      |
|:----------------------|---------------------:|:--------------------------:|
| BM_unsigned_cstr_to_num_v1<unsigned_long>_RMS | 24 | 30.20 (1) |
| BM_unsigned_cstr_to_num_v2<unsigned_long>_RMS | 59 | 6.49 (1) |
| BM_unsigned_cstr_to_num_v3<unsigned_long>_RMS | 55 | 6.80 (1) |
| BM_unsigned_cstr_to_num_v4<unsigned_long>_RMS | 58 | 7.58 (1) |
| **BM_unsigned_cstr_to_num_v5<unsigned_long>_RMS** | 60 | **7.34** (1) |
|----------------------|---------------------|--------------------------|
| BM_unsigned_cstr_to_num_v2<uint128_t>_RMS | 61 | 12.70 (1) |
| BM_unsigned_cstr_to_num_v3<uint128_t>_RMS | 58 | 12.68 (1) |
| BM_unsigned_cstr_to_num_v4<uint128_t>_RMS | 61 | 12.67 (1) |
| BM_unsigned_cstr_to_num_v5<uint128_t>_RMS | 60 | 12.89 (1) |

[Raw Benchmark results (unsigned long)](https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_long.txt)

<table>
    <tr>
    <td width="50%">unsigned long data (up to 64 bits) processed using various template instantiations of the function: unsigned short, unsigned int, unsigned long, unsigned __int128</td>
    <td>Same data, plotted without baseline: </td>
  </tr>
  <tr>
    <td><img src="https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_long.png"  alt="unsigned_cstr_to_num<int>"></td>
    <td><img src="https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_long_ignore_v1.png" alt="unsigned_cstr_to_num<int> (nobaseline)" ></td>
   </tr>
</table>

## Unsigned __int128 Data (up to 128 bits):

For unsigned int128 data, **v5** of the function is fastest.

|function version       | RMS                  | Big O                      |
|:----------------------|---------------------:|:--------------------------:|
| BM_unsigned_cstr_to_num_v2<uint128_t>_RMS | 65 | 24.61 (1) |
| BM_unsigned_cstr_to_num_v3<uint128_t>_RMS | 64 | 24.55 (1) |
| BM_unsigned_cstr_to_num_v4<uint128_t>_RMS | 64 | 24.98 (1) |
| *BM_unsigned_cstr_to_num_v5<uint128_t>_RMS* | 66 | *24.88* (1) |

[Raw Benchmark results (unsigned int128)](https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_uint128.txt)

<table>
  <tr>
    <td width="50%">unsigned int128 data (up to 128 bits) processed using various template instantiations of the function: unsigned short, unsigned int, unsigned long, unsigned __int128</td>
    <td>Same data, plotted without baseline: </td>
  </tr>
  <tr>
    <td><img src="https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_uint128.png"  alt="unsigned_cstr_to_num<uint128>"></td>
    <td><img src="https://github.com/pshoben/llutils/blob/master/data/benchmark_llutils_unsigned_cstr_to_num_uint128_ignore_v1.png" alt="unsigned_cstr_to_num<uint128> (nobaseline)" ></td>
   </tr> 
</table>

## Conclusions

1. Performance depends strongly on number of digits in the input, and on the width of the variable used to store the number.
2. On average, v5<unsigned int> is fastest on the reference architecture.  
3. Instantiating the function using the smallest width that can handle all expected input produces the best performance:
e.g. 32-bit integers run faster using the *unsigned int* instantiation than using the *unsigned long* one.
4. For 16-bit integers, using the *unsigned int* instantiation than using the *unsigned short* one.
5. On this build (gcc (GCC) 8.3.1 -O3) - pointer access into the buffer is faster than indexing, for all data widths.



