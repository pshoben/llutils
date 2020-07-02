#ifndef LLS_PROTODUMP_HPP
#define LLS_PROTODUMP_HPP 

#include <stdint.h>

namespace protodump {

#define DEFAULT_HOST    "127.0.0.1"
#define DEFAULT_LISTEN_PORT   6565
#define DEFAULT_RELAY_PORT    7575

#define MAX_CONN        16
#define MAX_EVENTS      32
#define BUF_SIZE        16
#define MAX_LINE        256

#ifndef __always_inline
# define __always_inline	inline __attribute__((always_inline))
#endif

extern bool g_verbose;
extern bool g_relay;
extern uint16_t g_listen_port;
extern uint16_t g_relay_to_port;

extern char g_relay_to_host[HOST_NAME_MAX+1];
extern char g_config_filename[PATH_MAX+1];

void load_config(const char * config_scope, const char * config_filename);
void server_run();
void connect_to_relay_target();

}

#endif

