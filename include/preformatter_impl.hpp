#ifndef LLUTILS_PREFORMATTER_IMPL_HPP
#define LLUTILS_PREFORMATTER_IMPL_HPP

#include <memory>
#include <string>
#include <vector>
#include <preformatter.hpp>

using std::string;
using std::vector;

namespace llutils::devtools {

	/* \class PreformatterImpl
	 * \brief a structure for describing message contents */
	class PreformatterImpl {
	public:
		void init(Preformatter * w);

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
		std::unique_ptr<Preformatted> preformat( const char * raw_bytes, size_t len ) ;
	private:
		string protocol_name;
		string protocol_version;
		Preformatter * pwrapper;
	};
}

#endif
