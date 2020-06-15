#include <gtest/gtest.h>
#include <iostream>
#include <llutils.hpp>
#include <limits.h>
#include <stdlib.h>

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
		unsigned short x = (x + (i * 1003)); // overflows
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
		unsigned int x = (x + (i * 104729)); // overflows
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
		unsigned long x = (x + (i * 104729)); // overflows
		sprintf(tmp,"%lu",x);
   		unsigned long y = LLUtils<unsigned long>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

TEST(LLUtils, StrToNumUnsignedLongLong) 
{
	unsigned long long max = ULLONG_MAX;
	EXPECT_EQ(LLUtils<unsigned long long>::unsigned_cstr_to_num("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<unsigned long long>::unsigned_cstr_to_num("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%llu",max);
	EXPECT_EQ(LLUtils<unsigned long long>::unsigned_cstr_to_num(tmp,strlen(tmp)),max);

	// mini fuzz
	unsigned long long x = 1;
	for( unsigned long long i = 0 ; i <= 1000 ; i++ ) {
		unsigned long long x = (x + (i * 104729)); // overflows
		sprintf(tmp,"%llu",x);
   		unsigned long y = LLUtils<unsigned long long>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}


TEST(LLUtils, StrToNumSignedShort) 
{
        short max = SHRT_MAX;
	EXPECT_EQ(LLUtils<short>::unsigned_cstr_to_num("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<short>::unsigned_cstr_to_num("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%hd",max);
	EXPECT_EQ(LLUtils<short>::unsigned_cstr_to_num(tmp,strlen(tmp)),max);

	// mini fuzz
	short x = 1;
	for( short i = 0 ; i <= 1000 ; i++ ) {
		short x = abs((short)(x + (i * 1009))); // overflows
		sprintf(tmp,"%hd",abs(x));
		//fprintf(stderr,"tmp = %s\n",tmp);
   		short y = LLUtils<short>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(int(y),int(abs(x)));
	}
}


TEST(LLUtils, StrToNumSignedInt) 
{
        int max = INT_MAX;
	EXPECT_EQ(LLUtils<int>::unsigned_cstr_to_num("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<int>::unsigned_cstr_to_num("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%d",max);
	EXPECT_EQ(LLUtils<int>::unsigned_cstr_to_num(tmp,strlen(tmp)),max);

	// mini fuzz
	int x = 1;
	for( int i = 0 ; i <= 1000 ; i++ ) {
		int x = abs(x + (i * 104729)); // overflows
		sprintf(tmp,"%d",x);
   		int y = LLUtils<int>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

TEST(LLUtils, StrToNumSignedLong) 
{
	long max = LONG_MAX;
	EXPECT_EQ(LLUtils<long>::unsigned_cstr_to_num("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<long>::unsigned_cstr_to_num("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%ld",max);
	EXPECT_EQ(LLUtils<long>::unsigned_cstr_to_num(tmp,strlen(tmp)),max);

	// mini fuzz
	long x = 1;
	for( long i = 0 ; i <= 1000 ; i++ ) {
		long x = abs(x + (i * 104729)); // overflows
		sprintf(tmp,"%ld",x);
   		long y = LLUtils<long>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

TEST(LLUtils, StrToNumSignedLongLong) 
{
	long long max = LLONG_MAX;
	EXPECT_EQ(LLUtils<long long>::unsigned_cstr_to_num("0",strlen("0")),0);
	EXPECT_EQ(LLUtils<long long>::unsigned_cstr_to_num("1",strlen("1")),1);

	char tmp[64];
	sprintf(tmp,"%lld",max);
	EXPECT_EQ(LLUtils<long long>::unsigned_cstr_to_num(tmp,strlen(tmp)),max);

	// mini fuzz
	long long x = 1;
	for( long long i = 0 ; i <= 1000 ; i++ ) {
		long long x = abs(x + (i * 104729)); // overflows
		sprintf(tmp,"%lld",x);
   		long long y = LLUtils<long long>::unsigned_cstr_to_num(tmp,strlen(tmp)); 
		EXPECT_EQ(y,x);
	}
}

