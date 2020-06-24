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

#if __GNUC__
#define LLUTILS_BUILTIN_EXPECT(b, t) (__builtin_expect(b, t))
#else
#define LLUTILS_BUILTIN_EXPECT(b, t) b
#endif

#define LLUTILS_LIKELY(x) LLUTILS_BUILTIN_EXPECT((x), 1)
#define LLUTILS_UNLIKELY(x) LLUTILS_BUILTIN_EXPECT((x), 0)

namespace llutils {

typedef unsigned __int128 uint128_t;

// baseline function v1
//#define unsigned_cstr_to_num_v1( buffer, len ) strtoul( buffer, 0, 10 )

// preferred implementation
#define unsigned_cstr_to_num( buffer, len ) unsigned_cstr_to_num_v5( buffer, len )

template <typename T>
class LLUtils
{
public:
	// forward to the preferred implementation
	template <typename... Args>
	static T unsigned_cstr_to_num_fwd(Args&& ... args)
	{
  		return unsigned_cstr_to_num_v5(std::forward<Args>(args)...);
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
	static T unsigned_cstr_to_num_v6( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		T result = 0;
		while LLUTILS_LIKELY((len--)) {
			result += powten[len] * (*buffer++ - '0');
		}
		return result;
	} 

private:
	static const T powten[std::numeric_limits<T>::digits10+1];
};
template<>
uint128_t LLUtils<uint128_t>::unsigned_cstr_to_num_v4( const char *buffer, size_t len )
{
	return LLUtils<uint128_t>::unsigned_cstr_to_num_v2(buffer,len);
}
template<>
uint128_t LLUtils<uint128_t>::unsigned_cstr_to_num_v5( const char *buffer, size_t len )
{
	return LLUtils<uint128_t>::unsigned_cstr_to_num_v2(buffer,len);
} 
template<>
uint128_t LLUtils<uint128_t>::unsigned_cstr_to_num_v6( const char *buffer, size_t len )
{
	return LLUtils<uint128_t>::unsigned_cstr_to_num_v2(buffer,len);
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
