#include "llutils.hpp"
#include <cstdio>
#include <cstring>
#include <sstream>

#include "llutils_harness_utils.hpp"

using namespace llutils;

typedef unsigned __int128 uint128_t;

void test_unsigned_short() {
	char in[64];
	// 0 value
	sprintf(in,"0");
	llutils_expect_value(LLUtils<unsigned short>::unsigned_cstr_to_num(in,strlen(in)),in);

	// MAX value
	unsigned short max = USHRT_MAX;
	sprintf(in,"%u",max);
	llutils_expect_value(LLUtils<unsigned short>::unsigned_cstr_to_num(in,strlen(in)),in);

	unsigned short low = rand() % USHRT_MAX;
	for( short i = 0 ; i <= 10 ; i++ ) {
		low = rand() % USHRT_MAX;
 		sprintf(in,"%0.4u",low);
		llutils_expect_value(LLUtils<unsigned short>::unsigned_cstr_to_num(in,strlen(in)),in);
	}
	for( short i = 0 ; i <= 10 ; i++ ) {
		low = low * rand() % USHRT_MAX; // overflows
 		sprintf(in,"%u",low);
		llutils_expect_value(LLUtils<unsigned short>::unsigned_cstr_to_num(in,strlen(in)),in);
	}
}


void test_unsigned_int() {
	char in[64];
	// 0 value
	sprintf(in,"0");
	llutils_expect_value(LLUtils<unsigned int>::unsigned_cstr_to_num(in,strlen(in)),in);

	// MAX value
	unsigned int max = UINT_MAX;
	sprintf(in,"%u",max);
	llutils_expect_value(LLUtils<unsigned int>::unsigned_cstr_to_num(in,strlen(in)),in);

	unsigned int low = rand() % UINT_MAX;

	// <19 digits mini fuzz (leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = rand() % UINT_MAX;
 		sprintf(in,"%0.9u",low);
		llutils_expect_value(LLUtils<unsigned int>::unsigned_cstr_to_num(in,strlen(in)),in);
	}
	// <19 mini fuzz (no leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = low * rand() % UINT_MAX; // overflows
 		sprintf(in,"%u",low);
		llutils_expect_value(LLUtils<unsigned int>::unsigned_cstr_to_num(in,strlen(in)),in);
	}
}


void test_unsigned_long() {

	char in[64];

	// 0 value
	sprintf(in,"0");
	llutils_expect_value(LLUtils<unsigned long>::unsigned_cstr_to_num(in,strlen(in)),in);

	// MAX value
	unsigned long max = ULONG_MAX;
	sprintf(in,"%lu",max);
	llutils_expect_value(LLUtils<unsigned long>::unsigned_cstr_to_num(in,strlen(in)),in);

	unsigned long low = rand() % ULONG_MAX;

	// <19 digits mini fuzz (leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = rand() % ULONG_MAX;
 		sprintf(in,"%0.19lu",low);
		llutils_expect_value(LLUtils<unsigned long>::unsigned_cstr_to_num(in,strlen(in)),in);
	}
	// <19 mini fuzz (no leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = low * rand() % ULONG_MAX; // overflows
 		sprintf(in,"%lu",low);
		llutils_expect_value(LLUtils<unsigned long>::unsigned_cstr_to_num(in,strlen(in)),in);
	}
}

void test_uint128() {

	char in[64];

	// 0 value
	sprintf(in,"0");
	print_convert_uint128_versions( in );

	// MAX value
	uint128_t max = ULLONG_MAX;
	sprintf(in,"%llu",max);
	print_convert_uint128_versions( in );

	unsigned long high = rand() % ULONG_MAX;
	unsigned long low = rand() % ULONG_MAX;

	// >19 digits mini fuzz (leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		high = rand() % ULONG_MAX;
		low = rand() % ULONG_MAX;
 		sprintf( in, "%0.19llu%0.19llu",high,low );
		print_convert_uint128_versions( in );
	}
	// >19 digits mini fuzz (no leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
 		high = high * rand() % ULONG_MAX; // overflows
		low = low * rand() % ULONG_MAX; // overflows
		uint128_to_cstr((uint128_t)high << 64 + (uint128_t)low, in, false);
		print_convert_uint128_versions( in );
	}
	// <19 digits mini fuzz (leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = rand() % ULONG_MAX;
 		sprintf(in,"%0.19llu",low);
		print_convert_uint128_versions( in );
	}
	// <19 mini fuzz (no leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = low * rand() % ULONG_MAX; // overflows
 		sprintf(in,"%.19llu",low);
		print_convert_uint128_versions( in );
	}
}


int main(void) {
	test_unsigned_short();
	test_unsigned_int();
	test_unsigned_long();
	test_uint128();
	printf("test harness exit\n\n");
}



