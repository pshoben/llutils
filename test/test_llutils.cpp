#include <gtest/gtest.h>
#include <iostream>
#include <llutils.hpp>
#include <limits.h>
#include <stdlib.h>
#include <cstdlib>

TEST(LLUtils, StrToNumUnsignedShort) 
{
        unsigned short max = USHRT_MAX;
	EXPECT_EQ(LLUtils<unsigned short>::unsigned_cstr_to_num_v3("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<unsigned short>::unsigned_cstr_to_num_v3("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%hu",max);
	EXPECT_EQ(LLUtils<unsigned short>::unsigned_cstr_to_num_v3(tmp,strlen(tmp)),max);

	// mini fuzz
	unsigned short x = 1;
	for( unsigned short i = 0 ; i <= 1009 ; i++ ) {
		unsigned short x = (x + (i * 1003)); // overflows
		sprintf(tmp,"%hu",x);
   		unsigned short y = LLUtils<unsigned short>::unsigned_cstr_to_num_v3(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}


TEST(LLUtils, StrToNumUnsignedInt) 
{
        unsigned int max = UINT_MAX;
	EXPECT_EQ(LLUtils<unsigned int>::unsigned_cstr_to_num_v3("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<unsigned int>::unsigned_cstr_to_num_v3("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%u",max);
	EXPECT_EQ(LLUtils<unsigned int>::unsigned_cstr_to_num_v3(tmp,strlen(tmp)),max);

	// mini fuzz
	unsigned int x = 1;
	for( unsigned int i = 0 ; i <= 1000 ; i++ ) {
		unsigned int x = (x + (i * 104729)); // overflows
		sprintf(tmp,"%u",x);
   		unsigned int y = LLUtils<unsigned int>::unsigned_cstr_to_num_v3(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

TEST(LLUtils, StrToNumUnsignedLong) 
{
	unsigned long max = ULONG_MAX;
	EXPECT_EQ(LLUtils<unsigned long>::unsigned_cstr_to_num_v3("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<unsigned long>::unsigned_cstr_to_num_v3("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%lu",max);
	EXPECT_EQ(LLUtils<unsigned long>::unsigned_cstr_to_num_v3(tmp,strlen(tmp)),max);

	// mini fuzz
	unsigned long x = 1;
	for( unsigned long i = 0 ; i <= 1000 ; i++ ) {
		unsigned long x = (x + (i * 104729)); // overflows
		sprintf(tmp,"%lu",x);
   		unsigned long y = LLUtils<unsigned long>::unsigned_cstr_to_num_v3(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

TEST(LLUtils, StrToNumUnsignedLongLong) 
{
	unsigned long long max = ULLONG_MAX;
	EXPECT_EQ(LLUtils<unsigned long long>::unsigned_cstr_to_num_v3("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<unsigned long long>::unsigned_cstr_to_num_v3("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%llu",max);
	EXPECT_EQ(LLUtils<unsigned long long>::unsigned_cstr_to_num_v3(tmp,strlen(tmp)),max);

	// mini fuzz
	unsigned long long x = 1;
	for( unsigned long long i = 0 ; i <= 1000 ; i++ ) {
		unsigned long long x = (x + (i * 104729)); // overflows
		sprintf(tmp,"%llu",x);
   		unsigned long y = LLUtils<unsigned long long>::unsigned_cstr_to_num_v3(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

