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
	
static void set_sockaddr(struct sockaddr_in *addr)
{
	bzero((char *)addr, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = INADDR_ANY;
	addr->sin_port = htons(g_port);
}

void client_run()
{
	int n;
	int c;
	int sockfd;
	char buf[MAX_LINE];
	struct sockaddr_in srv_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	set_sockaddr(&srv_addr);

	if (connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0) {
		perror("connect()");
		exit(1);
	}
	if( g_interactive ) {
		printf("Interactive mode.\n"
			"Enter q[+newline] to quit\n");

		for (;;) {
			printf("> ");
			fgets(buf, sizeof(buf), stdin);
			if( buf[0]=='q') {
				break;
			}
			c = strlen(buf) - 1;
			buf[c] = '\0';
			write(sockfd, buf, c + 1);
	
			bzero(buf, sizeof(buf));
			while (errno != EAGAIN
			       && (n = read(sockfd, buf, sizeof(buf))) > 0) {
				printf("echo: %s\n", buf);
				bzero(buf, sizeof(buf));
	
				c -= n;
				if (c <= 0) {
					break;
				}
			}
		}
	} else {
		int sent_count = 0 ;
		while( g_send_repeats == -1 || sent_count < g_send_repeats ) {
			strncpy(buf, g_send_string, sizeof(buf)-1);
			c = strlen(buf) - 1;
			write(sockfd, buf, c + 1);
			while (errno != EAGAIN && (n = read(sockfd, buf, sizeof(buf))) > 0) {
				bzero(buf, sizeof(buf));
				c -= n;
				if (c <= 0) {
					break;
				}
			}
			nanosleep( &g_send_wait, 0 );
			sent_count++;
		}
	}
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
	printf("client using host %s port %hu %s\n",g_host,g_port, g_interactive?"(interactive mode)":"(batch mode)");
	client_run();
	return 0;
}


