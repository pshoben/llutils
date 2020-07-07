#include <preformatter_impl.hpp>
#include <preformatter_fix.hpp>
#include <iostream>
#include <vector>
#include <memory>

using std::string;
using std::vector;

namespace llutils::devtools {

	void PreformatterImpl::init(Preformatter * w) {
		pwrapper = w;
	}

	vector<string> PreformatterImpl::get_supported_protocol_names() 
	{
		vector<string> v{"FIX"};
		return v;
	}
	vector<string> PreformatterImpl::get_supported_protocol_versions( string protocol_name ) 
	{
		vector<string> v{};
		return v;
	}

	void PreformatterImpl::set_protocol( string protocol_name,
					     string protocol_version ) 
	{
		this->protocol_name = protocol_name;
		this->protocol_version = protocol_version;
	}

	std::unique_ptr<Preformatted> PreformatterImpl::preformat( const char * raw_bytes, size_t len ) 
	{
		PreformatterFix fix;
		std::unique_ptr<Preformatted> pf = fix.preformat(raw_bytes, len );
		return std::move(pf);	
	}	

	void PreformatterImplDeleter::operator()(PreformatterImpl *p) { delete p ; } 
}
