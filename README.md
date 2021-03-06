# llutils

A header-only C++ library collection of utility functions commonly required for trading order entry workloads.

## Installation
```bash
# Check out the library.
$ git clone https://github.com/pshoben/llutils.git
```

## Building and running unit tests
```bash
# llutils requires googletest googlebenchmark to be cloned under third_party subfolder for building:
$ cd third_party
$ ./clone_dependencies.sh
$ cd ..

# llutils requires cmake3 for building
# install for rhel / centos :
$ sudo yum -i install cmake3

# create the build folder for out-of-source building:
$ mkdir build

# build it:
$ cd build ; cmake -DCMAKE_BUILD_TYPE=Release ..  ; make -j $(nproc)

# run the unit tests:
$ test/test_llutils

# set the working folder for storage benchmark results files and plots
$ export LLUTILS_DATA=/path/to/benchmark-out

# run the benchmarks:
$ benchmark/benchmark_llutils --benchmark_out_format=console --benchmark_out=$LLUTILS_DATA/benchmark_llutils.txt
$ benchmark/benchmark_llutils --benchmark-out-format=csv --benchmark-out=$LLUTILS_DATA/benchmark_llutils.csv
```

## Plotting results
```bash
# plotting results requires python3 with matplotlib numpy argparse libraries :
$ yum -y install python3
$ pip3 install matplotlib numpy argparse

# run the tool to produce the plot.
$ python3 tools/plot_results.py --input-file=${LLUTILS_DATA}/benchmark_llutils.csv --output-folder=${LLUTILS_DATA}
```

## Usage with cmake projects

llutils is a header-only c++ library. 

Add this line to your CMakeLists.txt file:

```bash
include(/path/to/llutils/include)
```

and #include the header file as needed:
```bash
#include <llutils.h>
```



## License

{llutils} is distributed under the MIT License
<https://github.com/pshoben/llutils/blob/master/LICENSE>


