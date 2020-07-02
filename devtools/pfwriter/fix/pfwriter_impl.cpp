#include <pfwriter_impl.hpp>
#include <iostream>

using std::string_view;

namespace llutils::devtools {

	//PfWriterImpl::PfWriterImpl()=default;
	//PfWriterImpl::~PfWriterImpl()=default;

	void PfWriterImpl::init(PfWriter * w) {
		pwrapper = w;
	}

	std::vector<string_view> PfWriterImpl::get_supported_formats() 
	{
		std::vector<string_view> v{};
		return v;
	}
	
	void PfWriterImpl::set_format( string_view format_type )
	{
		this->format_type = format_type;
	}
	
	void PfWriterImpl::write( std::unique_ptr<Preformatted> & message ) 
	{
	//	pwrapper->output_stream << to_string( message ) << std::endl;
	}

	string_view PfWriterImpl::to_string( unique_ptr<Preformatted> & message ) {
		return "";
	}
        
	void PfWriterImplDeleter::operator()(PfWriterImpl *p) { delete p ; } 
}
