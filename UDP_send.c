#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFERSIZE 1024
void sendMsg(int sock, char* ip, int port, char* msg, int len) {
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(ip);
	sa.sin_port = htons(port);

	int bytes_sent = sendto(sock, msg, len, 0, (struct sockaddr*) &sa, sizeof sa);
	if (bytes_sent < 0) {
		printf("Error sending data\n");
	}
	else {
		printf("Sent %d bytes\n", bytes_sent);
	}
}
int createSocket() {
	//creates a socket with UDP and datagrams
	//http://pubs.opengroup.org/onlinepubs/009695399/functions/socket.html
	int sock = socket(PF_INET,SOCK_DGRAM,0);

	if (sock == -1) {
		printf("Failed to create socket\n");
		return -1;
	}

	int broadcast = 1;
	//http://pubs.opengroup.org/onlinepubs/009695399/functions/setsockopt.html
	if (setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof broadcast) == -1) {
		printf("setsockopt (SO_BROADCAST) failed\n");
		return -1;
	}
	return sock;
}

