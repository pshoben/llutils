#ifndef llutils_harness_utils_hpp
#define llutils_harness_utils_hpp

#include <sstream>
#include <iostream>
#include <cstring>

using std::cout;
using std::endl;

std::ostream& operator<<(std::ostream& os, unsigned __int128 x){
    if(x<10) return  os << (char)(x+'0');
    return os << x/10 << (char)(x%10+'0');
}
std::ostream& operator<<(std::ostream& os, __int128 x){
    if(x<0) return os << "-" << -x;
    if(x<10) return  os << (char)(x+'0');
    return os << x/10 << (char)(x%10+'0');
}




void print_convert_uint128(const char * in)
{
	std::stringstream outss;
	std::string s;
	uint128_t y = LLUtils<uint128_t>::unsigned_cstr_to_num_v3(in,strlen(in));

	const char * orig = in;
	// strip leading zeroes from in
	const char * last_pos = in + strlen(in) -1 ;
	while( in < last_pos && *in == '0') {
		in++;
	}
	outss << y;
	s = outss.str();
	cout << " in = [" << orig << "] out = [" << y << "] match = " << (!strcmp(s.c_str(),in)?"TRUE":"FALSE") << endl;
}

void uint128_to_cstr(uint128_t x, char * dest, bool strip_leading_zeroes) 
{
	std::stringstream outss;
	std::string s;
	outss << x;
	s = outss.str();
	char in[64];
	strcpy( in, s.c_str());
	const char * p  = in;
	if( strip_leading_zeroes ) {
		const char * last_pos = in + strlen(in) -1 ;
		while( p < last_pos && *p == '0') {
			p++;
		}
	}
	//printf("uint128_to_cstr: %s p = %s\n",in,p);
	strcpy( dest, p );
}

template <typename T>
void llutils_expect_value( T val, const char * str) {
	//cout << "llutils_expect_value val = " << val << " str = [" << str << "] " << endl;
	uint128_t bigval = (uint128_t)val;
	char val_as_str[64];
	uint128_to_cstr( bigval, val_as_str, true );
	if( strcmp( val_as_str, str )) {
		printf("FAIL no match : num [%s] str [%s]\n", val_as_str, str );
	}
}
	
#endif
