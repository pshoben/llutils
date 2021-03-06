#ifndef LLUTILS_PREFORMATTED_HPP
#define LLUTILS_PREFORMATTED_HPP

#include <string>
#include <string_view>
#include <vector>

using std::string;
using std::string_view;
using std::vector;

namespace llutils::devtools {

	class PreformattedSection {
	public:
		string_view raw_bytes; /* raw bytes of a single field or subsection of the message */
		unsigned int offset; /* offset from the start of the top level message */
		unsigned int indent; /* number of levels of nesting, used for indentation */
		unsigned int field_id;
		string field_name;
		string field_value;
		string field_value_desc; /* useful where field value is member of an enumeration */
		vector<PreformattedSection> sections;
	};

	/* a structure for describing the contents of a raw message, in order to support later formatting and printing */
	class Preformatted {
	public:
		string_view raw_bytes; /* raw bytes of the whole message */
		unsigned int type_id;
		string type_name;
		string type_desc;
		vector<PreformattedSection> sections;
	};

}
#endif
