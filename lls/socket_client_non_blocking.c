/*
 * ref: https://github.com/onestraw/epoll-example 
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include <pthread.h>

#define DEFAULT_PORT    8080
#define DEFAULT_HOST    "127.0.0.1"

//#define MAX_CONN        16
//#define MAX_EVENTS      32
//#define BUF_SIZE        16
#define MAX_LINE        256

bool g_interactive = false;

unsigned short g_port= DEFAULT_PORT;
char g_host[HOST_NAME_MAX]=DEFAULT_HOST;
char g_send_string[MAX_LINE-1]="test send";
int g_send_repeats = -1 ; // default -1 = send forever
struct timespec g_send_wait;

int sockfd;
bool g_running = false;

static void set_sockaddr(struct sockaddr_in *addr)
{
	bzero((char *)addr, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(g_port);
}

void * recv_thread_function( void * args ) 
{
	printf("starting thread %s\n", __FUNCTION__ );
	int n;
	char buf[MAX_LINE];
	while( !g_running )
	{
		// do nothing until connected
	} 
	bzero(buf, sizeof(buf));
	n = read(sockfd, buf, sizeof(buf));

	bzero(buf, sizeof(buf));
	while ( g_running )
	{
		n = read(sockfd, buf, sizeof(buf));
		if( n > 0 ) {
			printf("client recv: %s\n", buf);
		}
		bzero(buf, sizeof(buf));
	}
	printf("exiting thread %s\n", __FUNCTION__ );
}


void client_run()
{
	int n;
	int c;
	//int sockfd;
	char buf[MAX_LINE];
	struct sockaddr_in srv_addr;

	sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	set_sockaddr(&srv_addr);

	// set to non-blocking
	//int flags = fcntl( sockfd, F_GETFL, 0 );
	//assert( flags != -1 );
	//fcntl( sockfd, F_SETFL, flags | O_NONBLOCK) ;


	int ret = connect( sockfd, (struct sockaddr *)&srv_addr, sizeof( srv_addr ));
	printf("connect returned %d.\n", ret);
	
	sleep(1);

	g_running = true;
	pthread_t recv_thread;
	int param;
	pthread_create( &recv_thread, NULL, recv_thread_function, &param );

	if( g_interactive ) {
		printf("Interactive mode.\n"
			"Enter q[+newline] to quit\n");

		for (;;) {
			printf("> ");
			fgets(buf, sizeof(buf), stdin);
			if( buf[0]=='q') {
				g_running = false;
				break;
			}
			c = strlen(buf) - 1;
			buf[c] = '\0';
			write(sockfd, buf, c + 1);
		}
	} else {
		int sent_count = 0 ;
		while( g_send_repeats == -1 || sent_count < g_send_repeats ) {
			strncpy(buf, g_send_string, sizeof(buf)-1);
			c = strlen(buf) - 1;
			write(sockfd, buf, c + 1);
			nanosleep( &g_send_wait, 0 );
			sent_count++;
		}
	}
	g_running = false;
	printf("joining recv_thread at %s\n", __FUNCTION__ );
	pthread_join( recv_thread, NULL );
	close(sockfd);
}


int main(int argc, char *argv[])
{
	g_send_wait.tv_sec=0;
	g_send_wait.tv_nsec=999999999;
	
	int opt;
	while ((opt = getopt(argc, argv, "ih:p:s:r:w:")) != -1) {
		switch (opt) {
		case 'i':
			g_interactive = true;
			break;
		case 'h':
			strcpy(g_host,optarg);
			break;
		case 'p':
			g_port = atoi(optarg);
			break;
		case 's':
			memset(g_send_string, 0, sizeof(g_send_string));
			strncpy(g_send_string,optarg,sizeof(g_send_string)-1);
			break;
		case 'r':
			g_send_repeats = atoi(optarg);
			break;
		case 'w':
			g_send_wait.tv_nsec = atol(optarg);
			if( g_send_wait.tv_nsec > 999999999 ) 
				g_send_wait.tv_nsec = 999999999;
			break;
		default:
			printf("usage: %s [-s send-string] [-w wait time (nanos)]\n"
		 		"[-r repeats (number of repeats)] [-i (interactive)]\n"
				"[h HOST] -p PORT\n", argv[0]);
			exit(1);
		}
	}
	printf("nonblocking client using host %s port %hu %s\n",g_host,g_port, g_interactive?"(interactive mode)":"(batch mode)");
	client_run();
	return 0;
}


