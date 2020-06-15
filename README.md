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
$ cd build

# build it:
$ cd build ; cmake -DCMAKE_BUILD_TYPE=Release ..  ; make -j $(nproc)

# run the unit tests:
$ test/test_llutils

# run the benchmarks:
$ benchmark/benchmark_llutils
```
## Usage with cmake projects

llutils is a header-only c++ library

```bash
# add this line to your CmakeLists.txt file:
include(/path/to/llutils/include)
```

and #include the header file as needed:
```bash
#include <llutils.h>
```



## License

{llutils} is distributed under the MIT License
<https://github.com/pshoben/llutils/blob/master/LICENSE>


