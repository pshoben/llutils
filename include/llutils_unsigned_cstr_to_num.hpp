#ifndef llutils_unsigned_cstr_to_num_hpp
#define llutils_unsigned_cstr_to_num_hpp

#include <cstdlib>
#include <type_traits>
#include <utility>

// baseline

#define unsigned_cstr_to_num_v1( buffer, len ) strtol( buffer, 0, 10 )

static const char * describe_unsigned_cstr_to_num[] = { "", 
						"atoi", 	// v1 baseline stdlib atoi 
						"strtol", 	// v2 baseline stdlib atoi
						"sequential" 	// v3 simple loop
					};
template <typename T>
class LLUtils
{
public:
	// forward to the preferred implementation
	template <typename... Args>
	static T unsigned_cstr_to_num(Args&& ... args)
	{
  		return unsigned_cstr_to_num_v2(std::forward<Args>(args)...);
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
};

#endif
