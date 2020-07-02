#include <cstdio>
#include <cstdlib>
#include <climits>
#include <unistd.h>
#include <config4cpp/Configuration.h>
#include "protodump.hpp"

using namespace protodump;

int main(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "f:")) != -1) {
		switch (opt) {
		case 'f':
			memset( protodump::g_config_filename, 0, sizeof( protodump::g_config_filename ));
			strncpy( protodump::g_config_filename, optarg, sizeof( protodump::g_config_filename )-1);
			break;
		default:
			printf("usage: %s -f config-filename\n", argv[0]);
			exit(1);
		}
	}
	if( strcmp( protodump::g_config_filename,"" )!=0) {
		protodump::load_config( "protodump", protodump::g_config_filename ) ;
	} else {
		printf("usage: %s -f config-filename\n", argv[0]);
		exit(1);
	}
	printf( "protodump listening on port %hu for relay to %s:%hu\n",
		protodump::g_listen_port,protodump::g_relay_to_host,protodump::g_relay_to_port );
	//protodump::connect_to_relay_target();
	protodump::server_run();
	return 0;
}

