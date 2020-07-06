#include <preformatter.hpp>
#include <preformatter_impl.hpp>

namespace llutils::devtools {

	Preformatter::Preformatter()
		: pImpl(new PreformatterImpl()) // custom deleter precludes make_unique
	{}

	void Preformatter::init() {
		pImpl->init(this);
	}

	vector<string> Preformatter::get_supported_protocol_names() 
	{
		return pImpl->get_supported_protocol_names();
	}

	vector<string> Preformatter::get_supported_protocol_versions( string protocol_name ) 
	{
		return pImpl-> get_supported_protocol_versions( protocol_name );
	}

	void Preformatter::set_protocol( string protocol_name , 
			   string protocol_version ) noexcept(false) 
	{
		pImpl->set_protocol( protocol_name, protocol_version ) ;
	}

	unique_ptr<Preformatted> Preformatter::preformat( const char * raw_bytes, size_t len ) 
	{
		return pImpl->preformat( raw_bytes, len ) ;
	}
}
