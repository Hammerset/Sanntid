#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void sendMsg(int sock, char* msg, int len) {
	int bytes_sent = send(sock, msg, len, MSG_DONTWAIT);
	if (bytes_sent < 0) {
		printf("Error sending data\n");
	} else {
		printf("Sent %d bytes\n", bytes_sent);
	}

	char buffer[1000];
	int read_bytes = read(sock, buffer, 1000);
	if (read_bytes < 0) {
		printf("Error reading\n");
		return;
	}

	printf("Recieved: %s\n", buffer);
}

int con(char* ip, int port) {
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (-1 == sock) {/* if socket failed to initialize, exit */
		printf("Failed to create socket\n");
		return -1;
	}

	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(ip);
	sa.sin_port = htons(port);

	if (-1 == connect(sock, (struct sockaddr*) &sa, sizeof(sa))) {
		printf("Connect failed\n");
		return -1;
	}

	return sock;
}

int main() {

	int port = 33546;
	char* ip = "129.241.187.23";
	printf("Sending to %s at %d\n", ip, port);

	int sock = con(ip, port);
	if (sock == -1)
		return 1;

	while (1) {
		char msg[100] = {0};
		fgets(msg, 100, stdin);
		int len = strlen(msg);
		if(len){
			msg[len-1] = 0;
			printf("Sending: \"%s\"\n", msg);

			sendMsg(sock, msg, len);
		}
		
	}

	shutdown(sock, SHUT_RDWR);
	close(sock);
}