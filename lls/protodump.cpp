//#include <asm/msr.h>
#include <sys/types.h> // conflict msr
#include <limits.h> // conflict msr
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <locale.h>
#include <config4cpp/Configuration.h>
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include "protodump.hpp"

//#include </root/kernel/linux-5.7.1/include/linux/getcpu.h>
//#ifdef _WIN32
//#include <intrin.h>
//#else
//#include <x86intrin.h>
//#endif
using namespace config4cpp;

namespace protodump {
bool g_verbose = true;
bool g_relay = true; // if true, relay mode else echo mode

uint16_t g_listen_port = DEFAULT_LISTEN_PORT;
uint16_t g_relay_to_port = DEFAULT_RELAY_PORT;

char g_relay_to_host[HOST_NAME_MAX+1]=DEFAULT_HOST; // TODO nyi
char g_config_filename[PATH_MAX+1]="";

int g_conn_sock_fd = 0;
int g_relay_sock_fd = 0 ;


inline uint32_t rdtsc32() {
  uint32_t low, high;
  __asm__ volatile (
   "rdtsc" /*  "lfence\n\trdtsc\n\tlfence" */
   : "=a"(low), "=d"(high)
   : "a"(0)
   : "%ecx");
  return low;
}

/*
 * register events of fd to epfd
 */
static void epoll_ctl_add(int epfd, int fd, uint32_t events)
{
	struct epoll_event ev;
	ev.events = events;
	ev.data.fd = fd;
	if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
		perror("epoll_ctl()\n");
		exit(1);
	}
}

static void set_sockaddr(struct sockaddr_in *addr)
{
	bzero((char *)addr, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(g_listen_port);
	printf("set_sockaddr port %hu\n",g_listen_port); fflush(stdout);

}

bool set_blocking(int fd, bool blocking)
{
   if (fd < 0) return false;

#ifdef _WIN32
   unsigned long mode = blocking ? 0 : 1;
   return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
#else
   int flags = fcntl(fd, F_GETFL, 0);
   if (flags == -1) return false;
   flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
#endif
}

static void set_relaysockaddr(struct sockaddr_in *addr)
{
	bzero((char *)addr, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(g_relay_to_port);
}


void connect_to_relay_target()
{
	struct sockaddr_in relay_addr;
	g_relay_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	set_relaysockaddr(&relay_addr);

	if (connect(g_relay_sock_fd, (struct sockaddr *)&relay_addr, sizeof(relay_addr)) < 0) {
		perror("connect() to relay target");
		// if fails to connect out to relay target, kill the client connection :
		close(g_conn_sock_fd);
		exit(1);
	}
	set_blocking(g_relay_sock_fd, false);
}

/*
 * epoll echo server
 */
void server_run()
{
//#define USE_CLOCK
#ifdef USE_CLOCK
struct timespec ts_start;
struct timespec ts_bfw; // before first write
struct timespec ts_end;
#else
	uint32_t tsc_start; // timestamp after epoll_wait returns
	uint32_t tsc_bfw; // timestamp before first write
	uint32_t tsc_end; // timestamp after finished write all bytes on relay target
#endif
	int i;
	int n;
	int epfd;
	int nfds;
	int listen_sock;
	socklen_t socklen;
	char read_buf[BUF_SIZE];
	//char write_buf[BUF_SIZE];

	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;
	struct epoll_event events[MAX_EVENTS];

	listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	set_sockaddr(&srv_addr);
	bind(listen_sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr));

	set_blocking(listen_sock, false);

	listen(listen_sock, MAX_CONN);

	epfd = epoll_create(1);

	epoll_ctl_add(epfd, listen_sock, EPOLLIN | EPOLLOUT | EPOLLET);
	if( g_relay && g_relay_sock_fd !=0 ) {
		epoll_ctl_add(epfd, g_relay_sock_fd, EPOLLIN | EPOLLOUT | EPOLLET);
	}

	socklen = sizeof(cli_addr);
	bool wrote_data=false;


	for (;;) {
		//printf("[+] before epoll_wait\n");
		nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
#ifdef USE_CLOCK
		clock_gettime(CLOCK_MONOTONIC, &ts_start);
#else
		tsc_start =rdtsc32(); // get hardware timestamp
#endif
// get clock precision/overhead
#ifdef USE_CLOCK
						clock_gettime( CLOCK_MONOTONIC, &ts_bfw );
#else
						tsc_bfw =rdtsc32(); // get hardware timestamp
#endif
		wrote_data=false;
		//printf("[+] after epoll_wait\n");
		for ( i = 0 ; i < nfds; i++ ) {
			//printf("[+] processing %d of <%d\n",i,nfds);
			if (events[i].data.fd == listen_sock) {
				/* handle new connection */
				g_conn_sock_fd =
				    accept(listen_sock,
					   (struct sockaddr *)&cli_addr,
					   &socklen);

				inet_ntop(AF_INET, (char *)&(cli_addr.sin_addr),
					  read_buf, sizeof(cli_addr));
				printf("[+] connected with %s:%d\n", read_buf,
				       ntohs(cli_addr.sin_port));
				set_blocking(g_conn_sock_fd, false);
				epoll_ctl_add(epfd, g_conn_sock_fd,
					      EPOLLPRI | EPOLLIN | EPOLLET | EPOLLRDHUP |
					      EPOLLHUP);
				// when client connects in, make the connection out to relay target and add it to epoll_wait list:
				connect_to_relay_target();
				if( g_relay && g_relay_sock_fd !=0 ) {
					epoll_ctl_add(epfd, g_relay_sock_fd, EPOLLIN | EPOLLOUT | EPOLLET);
				}
			} else if (events[i].events & EPOLLIN) {
				/* handle EPOLLIN event */
				int read_from_fd = events[i].data.fd;
				for (;;) {
					bzero(read_buf, sizeof(read_buf));
					//printf("[+] before read fd %d\n", read_from_fd);
					int remaining = read(read_from_fd, read_buf, sizeof(read_buf));
					//printf("[+] read returned : %d [%.*s]\n", remaining, remaining, read_buf);

					if ( remaining <= 0 /* || errno == EAGAIN */ ) {
						break;
					} else {
						int write_to_fd = 0;
						// if in relay mode, write to the 'other' socket
						if( g_relay ) {
							if( events[i].data.fd ==  g_relay_sock_fd ) {
								write_to_fd = g_conn_sock_fd;
								if( g_verbose )
									printf("[+] response: [%s] %lu %d\n", read_buf, strlen(read_buf), remaining);
							} else {
								write_to_fd = g_relay_sock_fd;
								if( g_verbose )
									printf("[+] relaying: [%s] %lu %d\n", read_buf, strlen(read_buf), remaining);
							}
						} else {
							//if( g_verbose )
							printf("[+] echoing: [%s] %lu %d\n", read_buf, strlen(read_buf), remaining );
							write_to_fd = read_from_fd;
						}
						char * p = read_buf;
						wrote_data=true;
//#ifdef USE_CLOCK
//						clock_gettime( CLOCK_MONOTONIC, &ts_bfw );
//#else
//						tsc_bfw =rdtsc32(); // get hardware timestamp
//#endif
						while( remaining > 0 ) {
							//printf("[+] before write [%.*s] fd %d (remaining = %d)\n", remaining,  p, write_to_fd, remaining);
							n = write(write_to_fd, p, remaining );
							//printf("[+] after write fd %d (wrote %d)\n", write_to_fd, n);
							if( n > 0 ) {
								p += n;
								remaining -= n;
							}
						}
	
					}
				}
#ifdef USE_CLOCK
				clock_gettime( CLOCK_MONOTONIC, &ts_end );
#else
				tsc_end =rdtsc32();
#endif
				if( g_relay && wrote_data ) {
#ifdef USE_CLOCK
					printf("[relay] start: [%ld] bfw: [%ld] diff-start-bfw: [%ld] end: [%ld] diff-bfw-end: [%ld]\n", 
							ts_start.tv_nsec, 
							ts_bfw.tv_nsec,
						 	ts_bfw.tv_nsec-ts_start.tv_nsec,
							ts_end.tv_nsec,
						 	ts_end.tv_nsec-ts_start.tv_nsec);
#else
					printf("[relay] start: [%u] bfw: [%u] diff-start-bfw [%u] end: [%u] diff-bfw-end [%u]\n",
							tsc_start, tsc_bfw, tsc_bfw-tsc_start, tsc_end, tsc_end-tsc_bfw );
#endif

				}
			} else {
				printf("[+] unexpected\n");
			}
			/* check if the connection is closing */
			if (events[i].events & (EPOLLRDHUP | EPOLLHUP)) {
				printf("[+] connection closed\n");
				epoll_ctl(epfd, EPOLL_CTL_DEL,
					  events[i].data.fd, NULL);
				close(events[i].data.fd);
				continue;
			}
		}
	}
}

void load_config(const char * config_scope, const char * config_filename) 
{
	printf( "reading config from [%s]\n", config_filename ) ;

	Configuration * cfg = Configuration::create();
	try {
		StringVector relay_maplist;
		cfg->parse( config_filename );
		cfg->lookupList( config_scope, "relay_maplist", relay_maplist );

		if( relay_maplist.length()>0 && relay_maplist.length() % 3 == 0 ) {

			g_relay = true;

			// read list in triples : from-port to-host to-port
			for( int i=0 ; i < relay_maplist.length()/3 ; i++ ) {

				g_listen_port = atoi( relay_maplist[i*3] );	

				memset( g_relay_to_host,0,sizeof( g_relay_to_host ));
				strncpy( g_relay_to_host, relay_maplist[i*3+1], HOST_NAME_MAX);

				g_relay_to_port = atoi( relay_maplist[i*3+2] );	
				printf( "relay from port %d -> %s:%d\n", g_listen_port, g_relay_to_host, g_relay_to_port );
			}
		}

	} catch(const ConfigurationException & ex) {
		std::cout << ex.c_str() << std::endl;
	}
	cfg->destroy();
}

}
