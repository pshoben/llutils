#ifndef llutils_unsigned_cstr_to_num_hpp
#define llutils_unsigned_cstr_to_num_hpp

#include <stdlib.h>
#include <type_traits>
#include <utility>
#include <limits>
#include <algorithm>
#include <limits.h>
//#include "llutils_harness_utils.hpp" 
#include <iostream>

#if defined(__GNUC__) || defined(__GNUG__)
#define LLUTILS_UNLIKELY(v) __builtin_expect(!!(v), 0)
#else
#define LLUTILS_UNLIKELY(v) v
#endif

namespace llutils {

typedef unsigned __int128 uint128_t;

// baseline function v1
//#define unsigned_cstr_to_num_v1( buffer, len ) strtoul( buffer, 0, 10 )

template <typename T>
class LLUtils
{
public:
	// forward to the preferred implementation
	template <typename... Args>
	static T unsigned_cstr_to_num(Args&& ... args)
	{
  		return unsigned_cstr_to_num_v4(std::forward<Args>(args)...);
	}

	static T unsigned_cstr_to_num_v1( const char *buffer, size_t len )
	{
		return strtoul( buffer, 0, 10 );
	}

	static T unsigned_cstr_to_num_v2( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		T result = 0;
		while (len--) {
			result = 10 * result + (*buffer++ - '0');
		}
		return result;
	}
 
	static T unsigned_cstr_to_num_v3( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		T result = 0;
		int i=0;
		while (len--) {
			result = 10 * result + (buffer[i++] - '0');
		}
		return result;
	} 

	static T unsigned_cstr_to_num_v4( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		T result = 0;
		int i=0;
		while (len--) {
			result += powten[len] * (buffer[i++] - '0');
		}
		return result;
	} 
	static T unsigned_cstr_to_num_v5( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		T result = 0;
		while (len--) {
			result += powten[len] * (*buffer++ - '0');
		}
		return result;
	} 

/*	static T unsigned_cstr_to_num_v5( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		T result_a = 0;
		T result_b = 0;
		int i=0;
		unsigned short count_a = 0;
		unsigned short count_b = 0;
		while (len--) {
			result_a = 100 * result_a + (buffer[i] - '0');
			if( len>1 ) {
				len--;
				result_b = 100 * result_b + (buffer[i+1] - '0');
				count_b++;
			}
			i++;
		}
		if( count_b == count_a )
			result_a = 10 * result_a;
		else
			result_b = 10 * result_b;
		return result_a + result_b;
	} 

	static T unsigned_cstr_to_num_v6( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		T result_a = 0;
		T result_b = 0;
		int i=0;
		while (len--) {
			result_a += powten[len] * (buffer[i++] - '0');
			if( len ) {
				len--;
				result_b = powten[len] * (buffer[i++] - '0');
			}
		}
		return result_a + result_b;
	} 
*/

private:
	static const T powten[std::numeric_limits<T>::digits10+1];
	static const uint128_t powten_uint128t[39];
};
template<>
uint128_t LLUtils<uint128_t>::unsigned_cstr_to_num_v4( const char *buffer, size_t len )
{
	uint128_t result = 0;
	int i=0;
	while (len--) {
		result += powten_uint128t[len] * (buffer[i++] - '0');
	}
	return result;
}
template<>
uint128_t LLUtils<uint128_t>::unsigned_cstr_to_num_v5( const char *buffer, size_t len )
{
	uint128_t result = 0;
	while (len--) {
		result += powten_uint128t[len] * (*buffer++ - '0');
	}
	return result;
} 

/*template<>
uint128_t LLUtils<uint128_t>::unsigned_cstr_to_num_v6( const char *buffer, size_t len )
{
	uint128_t result_a = 0;
	uint128_t result_b = 0;
	int i=0;
	while (len--) {
		result_a += powten_uint128t[len] * (buffer[i++] - '0');
		if( len ) {
			len--;
			result_b = powten_uint128t[len] * (buffer[i++] - '0');
		}
	}
	return result_a + result_b;
}*/ 


template <>
//constexpr uint128_t LLUtils<T>::powten[];
const uint128_t LLUtils<uint128_t>::powten_uint128t[39] = {
		1LLU,
		10LLU,
		100LLU,
		1000LLU,
		10000LLU,
		100000LLU,
		1000000LLU,
		10000000LLU,
		100000000LLU,
		1000000000LLU,

		10000000000LLU,
		100000000000LLU,
		1000000000000LLU,
		10000000000000LLU,
		100000000000000LLU,
		1000000000000000LLU,
		10000000000000000LLU,
		100000000000000000LLU,
		1000000000000000000LLU,
		10000000000000000000LLU,

		(uint128_t) 10000000000000000000LLU * (uint128_t) 10LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 100LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 1000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 10000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 100000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 1000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 10000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 100000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 1000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 10000000000LLU,

		(uint128_t) 10000000000000000000LLU * (uint128_t) 100000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 1000000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 10000000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 100000000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 1000000000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 10000000000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 100000000000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 1000000000000000000LLU,
		(uint128_t) 10000000000000000000LLU * (uint128_t) 10000000000000000000LLU // 2^128 = 3.4028237 x 10^38
	};
template <>
const unsigned long LLUtils<unsigned long>::powten[20] = {
		1LU,
		10LU,
		100LU,
		1000LU,
		10000LU,
		100000LU,
		1000000LU,
		10000000LU,
		100000000LU,
		1000000000LU,

		10000000000LU,
		100000000000LU,
		1000000000000LU,
		10000000000000LU,
		100000000000000LU,
		1000000000000000LU,
		10000000000000000LU,
		100000000000000000LU,
		1000000000000000000LU,
		10000000000000000000LLU
	};
template <>
const unsigned int LLUtils<unsigned int>::powten[10] = {
		1U,
		10U,
		100U,
		1000U,
		10000U,
		100000U,
		1000000U,
		10000000U,
		100000000U,
		1000000000U
	};
template <>
const unsigned short LLUtils<unsigned short>::powten[5] = {
		((unsigned short)1U),
		((unsigned short)10U),
		((unsigned short)100U),
		((unsigned short)1000U),
		((unsigned short)10000U)
	};

} // namespace
#endif
