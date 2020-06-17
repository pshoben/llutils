#include "llutils.hpp"
#include <cstdio>
#include <cstring>
#include <sstream>

#include "llutils_harness_utils.hpp"

typedef unsigned __int128 uint128_t;

void test1() {

	char in[64];

	// 0 value
	sprintf(in,"0");
	print_convert_uint128( in );

	// MAX value
	uint128_t max = ULLONG_MAX;
	sprintf(in,"%llu",max);
	print_convert_uint128( in );

	unsigned long high = rand() % ULONG_MAX;
	unsigned long low = rand() % ULONG_MAX;

	// >19 digits mini fuzz (leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		high = rand() % ULONG_MAX;
		low = rand() % ULONG_MAX;
 		sprintf( in, "%0.19llu%0.19llu",high,low );
		print_convert_uint128( in );
	}
	// >19 digits mini fuzz (no leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
 		high = high * rand() % ULONG_MAX; // overflows
		low = low * rand() % ULONG_MAX; // overflows
		uint128_to_cstr((uint128_t)high << 64 + (uint128_t)low, in, false);
		print_convert_uint128( in );
	}
	// <19 digits mini fuzz (leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = rand() % ULONG_MAX;
 		sprintf(in,"%0.19llu",low);
		print_convert_uint128( in );
	}
	// <19 mini fuzz (no leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = low * rand() % ULONG_MAX; // overflows
 		sprintf(in,"%.19llu",low);
		print_convert_uint128( in );
	}
}


int main(void) {
	test1();
	printf("test harness exit\n\n");
}



