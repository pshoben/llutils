
## Conclusions

1. Performance is very much dependent on number of digits in the input, and on the width of the variable used to store the number.
2. The optimal version changes depending on the workload. There is no version of the function that is optimal for all input data
3. Instantiating the function using the smallest width that can handle all expected input produces the best performance:
e.g. short integers run faster using the *unsigned short* instantiation than using the *unsigned int* one.


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
