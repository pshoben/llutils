#include <pfwriter_impl.hpp>
#include <iostream>

using std::string;
//using std::string_view;

namespace llutils::devtools {

	void PfWriterImpl::init(PfWriter * w) {
		pwrapper = w;
	}

	std::vector<string> PfWriterImpl::get_supported_formats() 
	{
		std::vector<string> v{};
		return v;
	}
	
	void PfWriterImpl::set_format( string format_type )
	{
		this->format_type = format_type;
	}

	void PfWriterImpl::write( PreformattedSection & pfs ) {
		ostream & out = pwrapper->output_stream;
		out << quote_string(string(pfs.raw_bytes)) << ","
			<< pfs.offset << ","
			// ignore indent level 
			<< pfs.field_id << ","
			<< quote_string(pfs.field_name) << ","
			<< quote_string(pfs.field_value) << ","
			<< quote_string(pfs.field_value_desc) << "\n";
		for( auto section : pfs.sections ) {
			write( section );
		}
	}	

	void PfWriterImpl::write( std::unique_ptr<Preformatted> & pf ) 
	{
		ostream & out = pwrapper->output_stream;
		out << quote_string(string(pf->raw_bytes)) << "," 
			<< pf->type_id << ","
			<< quote_string(pf->type_name) << ","
			<< quote_string(pf->type_desc) << "\n";
		for( auto section : pf->sections ) {
			write( section );
		}
	}


	string PfWriterImpl::quote_string( const string & s ) {
		if( s.find(',') != string::npos) {
			// comma found, need to quote the string
			return string("\"") + s + string("\"");
		} else {
			return s;
		}
	}

	void PfWriterImplDeleter::operator()(PfWriterImpl *p) { delete p ; } 
}
