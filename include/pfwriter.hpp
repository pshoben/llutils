#ifndef LLUTILS_PFWRITER_HPP
#define LLUTILS_PFWRITER_HPP

#include <iostream>
#include <memory>
#include <strings>
#include <vector>

using std::unique_ptr;

namespace llutils::devtools {

	/** \class PfWriter
	 *  \brief formats then writes a preformatted structure to a previously opened stream (e.g. file or stdout) 
	 *  this class does not provide methods for closing the stream or destroying the Preformatted object  
	 */ 
	class PfWriter {
	public:
		/** set the output stream */
		void set_ostream( std::ostream & stream );

		/** \returns a list of supported format options e.g. csv, xml, json, etc. 
		 */
		std::vector<string_view> get_supported_formats() ;

		/** select the output format e.g. csv, xml, json, ods
		 *  @throw if selected format is not supported (i.e. not in the list returned by get_supported_formats)  
		 */
		void set_format( std::string_view format_type ) noexcept(false) ;

		/** formats an object previously created by a Preformatter and writes it to the stream */
		void write( unique_ptr<Preformatted> & message ) ;
	private:
		struct PfWriterImpl;
		unique_ptr<PfWriterImpl> pImpl;
	};
}
#endif
