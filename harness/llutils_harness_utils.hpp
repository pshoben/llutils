#ifndef llutils_harness_utils_hpp
#define llutils_harness_utils_hpp

#include <sstream>
#include <iostream>
#include <cstring>
#include "llutils.hpp"

using std::cout;
using std::endl;

using namespace llutils;

std::ostream& operator<<(std::ostream& os, uint128_t x){
    if(x<10) return  os << (char)(x+'0');
    return os << x/10 << (char)(x%10+'0');
}
std::ostream& operator<<(std::ostream& os, int128_t x){
    if(x<0) return os << "-" << -x;
    if(x<10) return  os << (char)(x+'0');
    return os << x/10 << (char)(x%10+'0');
}

void print_convert_uint128(const char * in, int version)
{
	std::stringstream outss;
	std::string s;
	uint128_t y;
	switch ( version ) {
		case 0:
			y = LLUtils<uint128_t>::unsigned_cstr_to_num(in,strlen(in));
			break;
		case 1:
			y = LLUtils<uint128_t>::unsigned_cstr_to_num_v1(in,strlen(in));
			break;
		case 2:
			y = LLUtils<uint128_t>::unsigned_cstr_to_num_v2(in,strlen(in));
			break;
		case 3:
			y = LLUtils<uint128_t>::unsigned_cstr_to_num_v3(in,strlen(in));
			break;
		case 4:
			y = LLUtils<uint128_t>::unsigned_cstr_to_num_v4(in,strlen(in));
			break;
/*		case 5:
			y = LLUtils<uint128_t>::unsigned_cstr_to_num_v5(in,strlen(in));
			break;
		case 6:
			y = LLUtils<uint128_t>::unsigned_cstr_to_num_v6(in,strlen(in));
			break;
*/		default:
			printf("print_convert_uint128 : invalid function version - exiting\n");
			return;
	}
	const char * orig = in;
	// strip leading zeroes from in
	const char * last_pos = in + strlen(in) - 1 ;
	while( in < last_pos && *in == '0') {
		in++;
	}
	outss << y;
	s = outss.str();
	bool print_matches = false;
	bool match = !strcmp(s.c_str(),in);
	if( !match  || print_matches ) {
		printf("in print_convert_uint128 : version %d\n",version);
		cout << " expected = [" << orig << "] out = [" << y << "] match = " << (!strcmp(s.c_str(),in)?"TRUE":"FALSE") << endl;
	}
}
void print_convert_uint128_versions(const char * in)
{
	print_convert_uint128(in, 0);
	//print_convert_uint128(in, 1); // baseline
	print_convert_uint128(in, 2);
	print_convert_uint128(in, 3);
	print_convert_uint128(in, 4);
	//print_convert_uint128(in, 5);
	//print_convert_uint128(in, 6);

}

void uint128_to_cstr(uint128_t x, char * dest, bool strip_leading_zeroes) 
{
	std::stringstream sts;
	std::string s;
	sts << x;
	s = sts.str();
	char in[64];
	strcpy( in, s.c_str());
	const char * p  = in;
	if( strip_leading_zeroes ) {
		const char * last_pos = in + strlen(in) -1 ;
		while( p < last_pos && *p == '0') {
			p++;
		}
	}
	//printf("uint128_to_cstr: sts  = %s in = %s p = %s\n",sts.str().c_str(),in,p);
	strcpy( dest, p );
}

template <typename T>
void llutils_expect_value( T val, const char * str) {
	//cout << "llutils_expect_value val = " << val << " str = [" << str << "] " << endl;
	uint128_t bigval = (uint128_t)val;
	char val_as_str[64];
	uint128_to_cstr( bigval, val_as_str, true );
	// str might have leading zeroes
	const char * p = str;
	while ( *p && (*(p+1)) && *p == '0')
		p++;

	if( strcmp( val_as_str, p )) {
		printf("FAIL no match : num [%s] expected [%s]\n", val_as_str, str );
	}
}
	
#endif
