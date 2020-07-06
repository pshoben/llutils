#include <pfwriter.hpp>
#include <pfwriter_impl.hpp>


namespace llutils::devtools {

	PfWriter::PfWriter(ostream & stream)
		: output_stream(stream) 
		, pImpl(new PfWriterImpl()) // custom deleter precludes make_unique
	{}

	void PfWriter::init() {
		pImpl->init(this);
	}

	std::vector<string> PfWriter::get_supported_formats() 
	{
		return pImpl->get_supported_formats();
	}
	
	void PfWriter::set_format( std::string format_type )
	{
		pImpl->set_format( format_type );
	}
	
	void PfWriter::write( std::unique_ptr<Preformatted> & message ) 
	{
		pImpl->write( message );
	}
}
