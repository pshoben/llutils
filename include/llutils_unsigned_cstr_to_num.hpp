#ifndef llutils_unsigned_cstr_to_num_hpp
#define llutils_unsigned_cstr_to_num_hpp

#include <cstdlib>
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

typedef unsigned __int128 uint128_t;

// baseline function v1
#define unsigned_cstr_to_num_v1( buffer, len ) strtol( buffer, 0, 10 )

template <typename T>
class LLUtils
{
public:
	// forward to the preferred implementation
	template <typename... Args>
	static T unsigned_cstr_to_num(Args&& ... args)
	{
  		return unsigned_cstr_to_num_v5(std::forward<Args>(args)...);
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
		if(len>39)
			return std::numeric_limits<T>::max();
		T result_a = 0;
		T result_b = 0;
		while (len) {
			len--;
			result_a += powten[len] * (*buffer++ - '0');
			if (len) {
				len--;
				result_b += powten[len] * (*buffer++ - '0');
			}
		}
		return result_a + result_b;
	} 

	static T unsigned_cstr_to_num_v4( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");

		if(len>39)
			return std::numeric_limits<T>::max();
		T result_a = 0;
		T result_b = 0;
		T result_c = 0;
		while (len) {
			len--;
			result_a += powten[len] * (*buffer++ - '0');
			if (len) {
				len--;
				result_b += powten[len] * (*buffer++ - '0');
				if (len) {
					len--;
					result_c += powten[len] * (*buffer++ - '0');
				}
			}
		}
		return result_a + result_b + result_c;
	} 
	static T unsigned_cstr_to_num_v5( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		if(len>39)
			return std::numeric_limits<T>::max();
		T result_a = 0;
		T result_b = 0;
		T result_c = 0;
		T result_d = 0;
		while (len--) {
			result_a += powten[len] * (*buffer++ - '0');
			if (len) {
				len--;
				result_b += powten[len] * (*buffer++ - '0');
				if (len) {
					len--;
					result_c += powten[len] * (*buffer++ - '0');
					if (len) {
						len--;
						result_d += powten[len] * (*buffer++ - '0');
					}
				}
			}

		}
		return result_a + result_b + result_c + result_d;
	} 

private:
	static constexpr uint128_t powten[39] = {
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
	static const size_t MAX_DIGITS = sizeof(powten)/sizeof(uint128_t);
};

template <typename T>
constexpr uint128_t LLUtils<T>::powten[];

#endif
