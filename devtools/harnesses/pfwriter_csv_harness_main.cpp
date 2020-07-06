#include <cstdio>
//#include <cstdlib>
//#include <climits>
#include <iostream>
#include <string>

#include "preformatted.hpp"
#include "pfwriter.hpp"

using std::string;
using namespace llutils::devtools;

PreformattedSection create_section(unsigned int indent, unsigned int field_id, string field_name, string field_value, string field_value_desc ) 
{
	PreformattedSection ps;
	ps.raw_bytes = "section raw bytes";
	ps.offset = 0;
	ps.indent = indent;
	ps.field_id = field_id;
	ps.field_name = field_name;
	ps.field_value = field_value;
	ps.field_value_desc = field_value_desc;
	return ps;
}

int main()
{
	std::streambuf * buf = std::cout.rdbuf();
	std::ostream out(buf);

	std::unique_ptr<Preformatted> pf = std::make_unique<Preformatted>();
	pf->raw_bytes = "test_raw_bytes";
	pf->type_id = 1;
	pf->type_name = "test_type_name";
	pf->type_desc = "test_type,withcomma, desc";

	for( int i = 0 ; i < 10 ; i ++ ) {
		PreformattedSection section = create_section(  1, i, "field_name", "field_value", "field_value_desc" ) ;
		pf->sections.push_back(section);
	}
	PfWriter pfw(out);

	pfw.init();
	pfw.write(pf);

	std::cout << std::endl;

	return 0;
}

