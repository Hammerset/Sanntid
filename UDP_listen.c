#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>


void* listenAt(int port) {
	int sock = socket(PF_INET,SOCK_DGRAM,0);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(port);

	int yes = 1;
	int rc = setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
	if (rc == -1) {
		printf("failed to set SO_REUSEADDR\n");
	}

	if (-1 == bind(sock, (struct sockaddr*) &sa, sizeof sa)) {
		printf("failed to bind\n");
		return NULL;
	}

	char buffer[1024];
	socklen_t sasize = sizeof(sa);
	while (1) {
		int size = recvfrom(sock, (void*) buffer, sizeof buffer, 0, (struct sockaddr*) &sa, &sasize);
		if (size < 0)
		{
			printf("error recieving\n");
			return NULL;
		}
		buffer[size] = '\0';

		printf("From: %s\n", inet_ntoa(sa.sin_addr));
		printf("Length: %d\n", size);
		printf("%s\n", buffer);
	}

	printf("Not listening anymore\n");
}
int main() {
	int listenPort = 20001;
	printf("Listening at port %d\n", listenPort);

	listenAt(listenPort);

	return 0;
}