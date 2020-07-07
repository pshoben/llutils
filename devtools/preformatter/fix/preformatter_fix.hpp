#ifndef LLUTILS_PREFORMATTER_FIX_HPP
#define LLUTILS_PREFORMATTER_FIX_HPP

#include <preformatted.hpp>
#include <memory>
#include <vector>
#include <string>

using std::string;
using std::vector;

namespace llutils::devtools {

	class PreformatterFix {
	public:
		// TODO move to general utils
		vector<string> split(const string& str, char delim);
		PreformattedSection create_section_from_fix_tv( string tv_pair, 
								unsigned int offset,
			       					unsigned int indent);
		std::unique_ptr<Preformatted> preformat( const char * raw_bytes, size_t len );
	};
}

#endif
