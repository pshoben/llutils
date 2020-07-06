#ifndef LLUTILS_PREFORMATTER_HPP
#define LLUTILS_PREFORMATTER_HPP

#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::unique_ptr;

namespace llutils::devtools {

	/* \class Preformatter
	 * \brief a structure for describing message contents */
	class Preformatter {
	public:
		/** \returns a list of supported protocol names 
		 */
		vector<string> get_supported_protocol_names() ;

		/** \returns a list of supported versions for the protocol
		 */
		vector<string> get_supported_protocol_versions( string protocol_name ) ;

		/** select the input protocol e.g. FIX, T7 ETI v8.0 , LSE 
		 *  @throw if selected protocol version is not supported 
		 *  @throw i.e. not in the lists returned by get_supported_protocol_names and get_supported_protocol_versions  
		 */
		void set_protocol( string protocol_name , 
				   string protocol_version ) noexcept(false) ;

		/** \returns a pre-formatted object from a raw message */
		unique_ptr<Preformatted> preformat( const char * raw_bytes, size_t len ) ;
	private:
		struct PreformatterPimpl;
		unique_ptr<PreformatterPimpl> pImpl;
	};
}

#endif
