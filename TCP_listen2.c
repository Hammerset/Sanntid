#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* listenAt(int port) {
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	sa.sin_port = htons(port);

	if (-1 == bind(sock, (struct sockaddr*) &sa, sizeof sa)) {
		printf("Failed to bind\n");
		return NULL;
	}

	if (-1 == listen(sock, 10)) {
		printf("Failed to listen\n");
		return NULL;
	}

	while (1) {
		int connect = accept(sock, NULL, NULL);

		if (0 > connect) {
			printf("Failed to connect\n");
			return NULL;
		}

		char buffer[100];
		int read_bytes = read(connect, buffer, 1000);
		if (read_bytes < 0) {
			printf("Error reading\n");
			return NULL;
		}

		printf("Recieved: %s\n", buffer);

		sprintf(buffer, "Hello there");
		int send_len = strlen(buffer);
		buffer[send_len++] = '\0';

		int sent_bytes = send(connect, buffer, send_len,MSG_DONTWAIT);
		if (sent_bytes < 0) {
			printf("Error sending\n");
			return NULL;
		} else {
			printf("Sent %d bytes\n", sent_bytes);
		}

		
		if (-1 == shutdown(connect, SHUT_RDWR)) {
			printf("Can not shutdown\n");
			return NULL;
		}
		close(connect);
	}
}

int main() {
	
	int listenPort = 20001;
	printf("Listening at port %d\n", listenPort);

	listenAt(listenPort);

	return 0;
}