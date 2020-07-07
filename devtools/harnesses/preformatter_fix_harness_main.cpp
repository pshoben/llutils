#include <cstdio>
//#include <cstdlib>
//#include <climits>
#include <iostream>
#include <string>

#include "preformatted.hpp"
#include "pfwriter.hpp"
#include "preformatter.hpp"

using std::string;
using namespace llutils::devtools;

PreformattedSection create_section(unsigned int indent, unsigned int field_id, string field_name, string field_value, string field_value_desc ) 
{
	PreformattedSection ps;
	ps.raw_bytes = "";
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

	Preformatter pfm{};
	pfm.init();

	std::unique_ptr<Preformatted> pf = std::make_unique<Preformatted>();
	pf->raw_bytes = "";
	pf->type_id = 1;
	pf->type_name = "FIX";
	pf->type_desc = "a fix message";

	pf->sections.push_back(create_section(  1, 8, "BeginString", "FIX4.2", "" )) ;
	pf->sections.push_back(create_section(  1, 9, "BodyLength", "999", "" )) ;
	pf->sections.push_back(create_section(  1, 35, "MsgType", "D", "" )) ;
	pf->sections.push_back(create_section(  1, 49, "SenderCompID", "SenderSubID", "" )) ;
	pf->sections.push_back(create_section(  1, 50, "SenderSubID", "SenderSubID", "" )) ;
	pf->sections.push_back(create_section(  1, 56, "TargetCompID", "TargetCompID", "" )) ;
	pf->sections.push_back(create_section(  1, 57, "TargetSubID", "TargetSubID", "" )) ;

	string fixstr = "8=FIX\0019=100\00135=D\00149=SenderCompID\00156=TargetCompID\001";
	std::unique_ptr<Preformatted> pf2 = pfm.preformat( fixstr.c_str(), fixstr.size());

	PfWriter pfw{out};

	pfw.init();
	pfw.write(pf);
	pfw.write(pf2);

	std::cout << std::endl;

	return 0;
}

