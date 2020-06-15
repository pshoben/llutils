#ifndef llutils_hpp
#define llutils_hpp

#define llutils_VERSION_MAJOR 0
#define llutils_VERSION_MINOR 1

template <typename T>
class LLUtils
{
public:
	static T unsigned_cstr_to_num( const char *buffer, size_t len )
	{
		T result = 0;
		while (len--) {
			result = 10 * result + (*buffer++ - '0');
		}
		return result;
	}       

};

#endif
