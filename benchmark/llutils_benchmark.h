#ifndef llutils_benchmark_hpp
#define llutils_benchmark_hpp

#include <stdio.h>

void llutils_benchmark_print_summary_header() {
	printf("\n");
	printf("|function version       | RMS                  | Big O                      |\n");
	printf("|:----------------------|---------------------:|:--------------------------:|\n");
}

#endif
