/*
 * ref: https://github.com/onestraw/epoll-example/blob/master/epoll.c 
 */
#include <sys/types.h>
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
#include <limits.h>

#define DEFAULT_HOST    "127.0.0.1"
#define DEFAULT_LISTEN_PORT   6565
#define DEFAULT_RELAY_PORT    7575

#define MAX_CONN        16
#define MAX_EVENTS      32
#define BUF_SIZE        16
#define MAX_LINE        256

static bool g_relay = false;  // if true, relay mode else echo mode
static uint16_t g_listen_port = DEFAULT_LISTEN_PORT;
static uint16_t g_relay_to_port = DEFAULT_RELAY_PORT;

char g_relay_to_host[HOST_NAME_MAX+1]=DEFAULT_HOST; // TODO nyi

static int g_conn_sock_fd = 0;
static int g_relay_sock_fd = 0 ;

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
		exit(1);
	}
	set_blocking(g_relay_sock_fd, false);
}

/*
 * epoll echo server
 */
void server_run()
{
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
	for (;;) {
		//printf("[+] before epoll_wait\n");
		nfds = epoll_wait(epfd, events, MAX_EVENTS, -1);
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
								printf("[+] response: [%s] %lu %d\n", read_buf, strlen(read_buf), remaining);
							} else {
								write_to_fd = g_relay_sock_fd;
								printf("[+] relaying: [%s] %lu %d\n", read_buf, strlen(read_buf), remaining);
							}
						} else {
							printf("[+] echoing: [%s] %lu %d\n", read_buf, strlen(read_buf), remaining );
							write_to_fd = read_from_fd;
						}
						char * p = read_buf;
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


int main(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "rh:p:l:")) != -1) {
		switch (opt) {
		case 'r':
			g_relay = true;
			break;
		case 'h':
			memset(g_relay_to_host,0,sizeof(g_relay_to_host));
			strncpy(g_relay_to_host,optarg, HOST_NAME_MAX);
			break;
		case 'p':
			g_relay_to_port = atoi(optarg);
			break;
		case 'l':
			g_listen_port = atoi(optarg);
			break;
		default:
			printf("usage: %s [-r [-h relay-to-host] [-p relay-to-port] [-l listen-port]\n", argv[0]);
			exit(1);
		}
	}
	printf("server listening on port %hu : relay mode = %d\n", g_listen_port, g_relay);
	if( g_relay ) {
		printf("relay to %s:%hu\n",g_relay_to_host, g_relay_to_port);
		connect_to_relay_target();
	}
	server_run();
	return 0;
}

