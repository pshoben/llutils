#include <gtest/gtest.h>
#include <iostream>
#include <llutils.hpp>
#include <limits.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include "llutils_harness_utils.hpp"

using namespace llutils;

TEST(LLUtils, StrToNumUnsignedShort) 
{
	unsigned short max = USHRT_MAX;
	EXPECT_EQ(LLUtils<unsigned short>::unsigned_cstr_to_num("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<unsigned short>::unsigned_cstr_to_num("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%hu",max);
	EXPECT_EQ(LLUtils<unsigned short>::unsigned_cstr_to_num(tmp,strlen(tmp)),max);

	// mini fuzz
	unsigned short x = 1;
	for( unsigned short i = 0 ; i <= 1009 ; i++ ) {
		x = (x + (i * 1003)); // overflows
		sprintf(tmp,"%hu",x);
   		unsigned short y = LLUtils<unsigned short>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}


TEST(LLUtils, StrToNumUnsignedInt) 
{
        unsigned int max = UINT_MAX;
	EXPECT_EQ(LLUtils<unsigned int>::unsigned_cstr_to_num("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<unsigned int>::unsigned_cstr_to_num("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%u",max);
	EXPECT_EQ(LLUtils<unsigned int>::unsigned_cstr_to_num(tmp,strlen(tmp)),max);

	// mini fuzz
	unsigned int x = 1;
	for( unsigned int i = 0 ; i <= 1000 ; i++ ) {
		x = (x + (i * 104729)); // overflows
		sprintf(tmp,"%u",x);
   		unsigned int y = LLUtils<unsigned int>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

TEST(LLUtils, StrToNumUnsignedLong) 
{
	unsigned long max = ULONG_MAX;
	EXPECT_EQ(LLUtils<unsigned long>::unsigned_cstr_to_num("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<unsigned long>::unsigned_cstr_to_num("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%lu",max);
	EXPECT_EQ(LLUtils<unsigned long>::unsigned_cstr_to_num(tmp,strlen(tmp)),max);

	// mini fuzz
	unsigned long x = 1;
	for( unsigned long i = 0 ; i <= 1000 ; i++ ) {
		x = (x + (i * 104729)); // overflows
		sprintf(tmp,"%lu",x);
   		unsigned long y = LLUtils<unsigned long>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

TEST(LLUtils, StrToNumU128T) 
{
	char in[64];
	char in_nozeroes[64];
	char out[64];

	// 0 value
	sprintf(in,"0");
	EXPECT_EQ(LLUtils<uint128_t>::unsigned_cstr_to_num(in,strlen(in)),0);

	// MAX value
	uint128_t max = ULLONG_MAX;
	sprintf(in,"%llu",(unsigned long long)max);
	uint128_to_cstr( LLUtils<uint128_t>::unsigned_cstr_to_num(in,strlen(in)),out, true );
	EXPECT_STREQ(in,out);

	unsigned long long high = rand() % ULONG_MAX;
	unsigned long long low = rand() % ULONG_MAX;

	// >19 digits mini fuzz (leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		high = rand() % ULONG_MAX;
		low = rand() % ULONG_MAX;
 		sprintf( in, "%019llu%019llu",high,low );
		sprintf( in_nozeroes, "%llu%019llu",high,low );
		uint128_to_cstr( LLUtils<uint128_t>::unsigned_cstr_to_num(in,strlen(in)),out, true );
		EXPECT_STREQ(in_nozeroes,out);
	}
	// >19 digits mini fuzz (no leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
 		high = high * rand() % ULONG_MAX; // overflows
		low = low * rand() % ULONG_MAX; // overflows
		uint128_to_cstr(((uint128_t)high << 64) + ((uint128_t)low), in, true );
		uint128_to_cstr(LLUtils<uint128_t>::unsigned_cstr_to_num(in,strlen(in)),out, true );
		EXPECT_STREQ(in,out);
	}
	// <19 digits mini fuzz (leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = rand() % ULONG_MAX;
 		sprintf(in,"%019llu",low);
		sprintf( in_nozeroes, "%llu",low );
		uint128_to_cstr(LLUtils<uint128_t>::unsigned_cstr_to_num(in,strlen(in)),out, true );
		EXPECT_STREQ(in_nozeroes,out);
	}
	// <19 mini fuzz (no leading zeroes)
	for( int i = 0 ; i <= 10 ; i++ ) {
		low = low * rand() % ULONG_MAX; // overflows
 		sprintf(in,"%llu",low);
		uint128_to_cstr(LLUtils<uint128_t>::unsigned_cstr_to_num(in,strlen(in)),out, true );
		EXPECT_STREQ(in,out);
	}
}


