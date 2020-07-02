#include <cstdio>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <string_view>
#include <string>

#include "preformatted.hpp"
#include "pfwriter.hpp"

using namespace llutils::devtools;

int main()
{
	std::streambuf * buf = std::cout.rdbuf();
	std::ostream out(buf);

	std::unique_ptr<Preformatted> pf = std::make_unique<Preformatted>();
	pf->raw_bytes = "test_raw_bytes";
	pf->type_id = 1;
	pf->type_name = "test_type_name";
	pf->type_desc = "test_type desc";
	
	PfWriter pfw;

	pfw.init();
	pfw.write(pf);
	return 0;
}

