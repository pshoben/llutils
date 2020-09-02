#ifndef llutils_unsigned_cstr_to_num_hpp
#define llutils_unsigned_cstr_to_num_hpp

#include <cstdlib>
#include <cstring>
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

//typedef unsigned __int128 uint128_t;

// baseline function v1
//#define unsigned_cstr_to_num_v1( buffer, len ) strtoul( buffer, 0, 10 )

// preferred implementation
//#define unsigned_cstr_to_num( buffer, len ) unsigned_cstr_to_num_v5( buffer, len )

template <typename T, int S = 0 > /* size  0 = unused */
class LLUtils
{
public:
	// forward to the preferred implementation
	template <typename... Args>
	static T unsigned_cstr_to_num(Args&& ... args)
	{
  		//return unsigned_cstr_to_num_v5(std::forward<Args>(args)...);

		// forward to v7 (version with 2x template parameters)
		//printf("in universal forwarding function\n");
  		return unsigned_cstr_to_num_v7(std::forward<Args>(args)...);
	}

	static T unsigned_cstr_to_num_v1( const char *buffer, size_t len __attribute__((unused)))
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
		while (len) {
			result += powten[len] * (buffer[i++] - '0');
			len--;
		}
		return result;
	} 
	static T unsigned_cstr_to_num_v5( const char *buffer, size_t len )
	{
		static_assert(std::is_unsigned<T>::value,"");
		T result = 0;
		while (len) {
			result += powten[len] * (*buffer++ - '0');
			len--;
		}
		return result;
	} 

	static T unsigned_cstr_to_num_v6( const char *buffer, size_t len )
	{
		//printf("#a1 %s: len= %d\n",__FUNCTION__, len);

		static_assert(std::is_unsigned<T>::value,"");
		T result = 0;
		while LLUTILS_LIKELY(len) {
			result += LLUtils<T,0>::powten[len] * (*buffer++ - '0');
			len--;
		}
		return result;
	} 

	static T unsigned_cstr_to_num_v7_fixed_len( const char *buffer ) 
	{
		T result = 0;
		int len = S;
		//printf("#3 %s: len= %d\n",__FUNCTION__, len);
		while( len ) {
			//printf("#4 %s: %c=%d * powten[%d]%d = %d\n",__FUNCTION__,*buffer,(*buffer - '0'),len,LLUtils<T,0>::powten[len],LLUtils<T,0>::powten[len] * (*buffer - '0'));
			result += LLUtils<T,0>::powten[len] * (*buffer++ - '0');
			len--;
		} 
		//printf("%s: %c  = %d\n",__FUNCTION__, *buffer,(*buffer - '0'));
		//result += *buffer - '0';
		return result;
	} 

	static T unsigned_cstr_to_num_v7( const char *buffer, size_t len )
	{
		//printf("#5 %s:%s:%d buffer = [%s] strlen buffer = [%u] len = [%u]\n",__FUNCTION__, __FILE__, __LINE__, buffer, strlen(buffer),len);
		switch( len ) {
		case 0:
			return (T) 0;
		case 1:
			return LLUtils<T, 1>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 2:
			return LLUtils<T, 2>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 3:
			return LLUtils<T, 3>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 4:
			return LLUtils<T, 4>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 5:
			return LLUtils<T, 5>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 6:
			return LLUtils<T, 6>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 7:
			return LLUtils<T, 7>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 8:
			return LLUtils<T, 8>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 9:
			return LLUtils<T, 9>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 10:
			return LLUtils<T, 10>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 11:
			return LLUtils<T, 11>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 12:
			return LLUtils<T, 12>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 13:
			return LLUtils<T, 13>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 14:
			return LLUtils<T, 14>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 15:
			return LLUtils<T, 15>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		case 16:
			return LLUtils<T, 16>::unsigned_cstr_to_num_v7_fixed_len( buffer );
		default:
			//printf("#1 %s: buffer = [%s] strlen buffer = [%u] len = [%u] calling v6\n",__FUNCTION__, buffer, strlen(buffer),len);
			return unsigned_cstr_to_num_v6( buffer, len );
		}
	} 
	static const T powten[std::numeric_limits<T>::digits10+2];
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
template<>
uint128_t LLUtils<uint128_t>::unsigned_cstr_to_num_v7( const char *buffer, size_t len )
{
	//printf("#2 %s:%s:%d buffer = [%s] strlen buffer = [%u] len = [%u]\n",__FUNCTION__, __FILE__, __LINE__, buffer, strlen(buffer),len);
	return LLUtils<uint128_t>::unsigned_cstr_to_num_v2(buffer,len);
} 


template <>
const unsigned long LLUtils<unsigned long>::powten[21] = {
		0LU,
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
const unsigned int LLUtils<unsigned int>::powten[11] = {
		0U,
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
const unsigned short LLUtils<unsigned short>::powten[6] = {
		((unsigned short)0U),
		((unsigned short)1U),
		((unsigned short)10U),
		((unsigned short)100U),
		((unsigned short)1000U),
		((unsigned short)10000U)
	};

template<>
unsigned short LLUtils<unsigned short>::unsigned_cstr_to_num_v7( const char *buffer, size_t len )
{
	//printf("#3 %s:%s:%d buffer = [%s] strlen buffer = [%u] len = [%u]\n",__FUNCTION__, __FILE__, __LINE__, buffer, strlen(buffer),len);
	switch( len ) {
	case 1:
		return LLUtils<unsigned short, 1>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 2:
		return LLUtils<unsigned short, 2>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 3:
		return LLUtils<unsigned short, 3>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 4:
		return LLUtils<unsigned short, 4>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 5:
		return LLUtils<unsigned short, 5>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	default:
		return unsigned_cstr_to_num_v6( buffer, len );
	}
} 


template<>
unsigned int LLUtils<unsigned int>::unsigned_cstr_to_num_v7( const char *buffer, size_t len )
{
	//printf("#3 %s:%s:%d buffer = [%s] strlen buffer = [%u] len = [%u]\n",__FUNCTION__, __FILE__, __LINE__, buffer, strlen(buffer),len);
	switch( len ) {
	case 1:
		return LLUtils<unsigned int, 1>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 2:
		return LLUtils<unsigned int, 2>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 3:
		return LLUtils<unsigned int, 3>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 4:
		return LLUtils<unsigned int, 4>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 5:
		return LLUtils<unsigned int, 5>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 6:
		return LLUtils<unsigned int, 6>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 7:
		return LLUtils<unsigned int, 7>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 8:
		return LLUtils<unsigned int, 8>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 9:
		return LLUtils<unsigned int, 9>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	case 10:
		return LLUtils<unsigned int, 10>::unsigned_cstr_to_num_v7_fixed_len( buffer );
	default:
		return unsigned_cstr_to_num_v6( buffer, len );
	}
} 

} // namespace
#endif
