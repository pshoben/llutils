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
	
	void PfWriterImpl::write( std::unique_ptr<Preformatted> & pf ) 
	{
		ostream & out = pwrapper->output_stream;
		out << pf->raw_bytes << "," 
			<< pf->type_id << ","
			<< pf->type_name << ","
			<< pf->type_desc << "\n";
	}

//	string_view PfWriterImpl::to_string( unique_ptr<Preformatted> & pf ) {
//		ostream &  out = pwrapper->output_stream;
//		out << pf->raw_bytes << "," 
//			<< pf->type_id << ","
//			<< pf->type_name << ","
//			<< pf->type_desc << "\n";
//	}
        
	void PfWriterImplDeleter::operator()(PfWriterImpl *p) { delete p ; } 
}
