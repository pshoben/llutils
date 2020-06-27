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

#define DEFAULT_PORT    8080
#define DEFAULT_HOST    "127.0.0.1"

//#define MAX_CONN        16
//#define MAX_EVENTS      32
//#define BUF_SIZE        16
#define MAX_LINE        256

unsigned short g_port= DEFAULT_PORT;
char g_host[HOST_NAME_MAX]=DEFAULT_HOST;

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

	for (;;) {
		printf("input: ");
		fgets(buf, sizeof(buf), stdin);
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
	close(sockfd);
}


int main(int argc, char *argv[])
{
	int opt;
	while ((opt = getopt(argc, argv, "h:p:")) != -1) {
		switch (opt) {
		case 'h':
			strcpy(g_host,optarg);
			break;

		case 'p':
			g_port = atoi(optarg);
			break;
		default:
			printf("usage: %s [h HOST] -p PORT\n", argv[0]);
			exit(1);
		}
	}
	printf("client using host %s port %hu\n",g_host,g_port);
	client_run();
	return 0;
}


