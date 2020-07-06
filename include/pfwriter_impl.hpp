#ifndef LLUTILS_PFWRITER_IMPL_HPP
#define LLUTILS_PFWRITER_IMPL_HPP

#include <iostream>
#include <memory>
#include <string>
//#include <string_view>
#include <vector>
#include <preformatted.hpp>
#include <pfwriter.hpp>

//using std::unique_ptr;
using std::string;
using std::ostream;
using std::string;
//using std::string_view;

namespace llutils::devtools {

	/** \class PfWriterImpl
	 *  \brief formats then writes a preformatted structure to a previously opened stream (e.g. file or stdout) 
	 *  this class does not provide methods for closing the stream or destroying the Preformatted object  
	 */ 
	class PfWriterImpl {
	public:
		void init(PfWriter * w);

		/** \returns a list of supported format options e.g. csv, xml, json, etc. 
		 */
		std::vector<string> get_supported_formats() ;

		/** select the output format e.g. csv, xml, json, ods
		 *  @throw if selected format is not supported (i.e. not in the list returned by get_supported_formats)  
		 */
		void set_format( string format_type ) noexcept(false) ;

		/** formats an object previously created by a Preformatter and writes it to the stream */
		void write( std::unique_ptr<Preformatted> & pf ) ;
		void write( PreformattedSection & pfs ) ;
	private:
		string quote_string( const string & s );
		string format_type;
		PfWriter * pwrapper;
	};
}
#endif
