#include <preformatter_fix.hpp>
#include <vector>
#include <utility>
#include <iostream>

using std::string;
using std::vector;

namespace llutils::devtools {

	// TODO move to general utils
	vector<string> PreformatterFix::split(const string& str, char delim) {
		vector<string> vec;
		size_t start;
		size_t end = 0;
		while (( start = str.find_first_not_of(delim, end)) != string::npos) {
			end = str.find(delim, start);
			vec.push_back(str.substr(start, end - start));
		}
		return vec;
	}

	PreformattedSection PreformatterFix::create_section_from_fix_tv( string tv_pair, 
									unsigned int offset,
		       							unsigned int indent)
	{	
		PreformattedSection sec;
		vector<string> vec = split( tv_pair, '=' );
	       	if( vec.size() == 2 ) {
			//sec.raw_bytes = string_view{ tv_pair };
			sec.offset = offset;
			sec.indent = indent;
			sec.field_id = (unsigned int) atoi( vec[0].c_str() );
			sec.field_name = vec[0];
			sec.field_value = vec[1];
			sec.field_value_desc = vec[1];
		}
		return sec;
	}

	std::unique_ptr<Preformatted> PreformatterFix::preformat( const char * raw_bytes, size_t len ) 
	{
		std::unique_ptr<Preformatted> pf = std::make_unique<Preformatted>(Preformatted());
		pf->raw_bytes = string_view(raw_bytes, len);
		vector<string> vec = split( string{pf->raw_bytes}, '\001' );

		unsigned int offset = 0;
		for( string s : vec ) {
			pf->sections.push_back( create_section_from_fix_tv( s, offset, 1 )) ;
			offset += s.size() + 1;
		}
		return std::move(pf);
	}	

}
