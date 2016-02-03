
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "network.h"

int main() {
	int port = 20001;
	int masterSocket = createSocket();
	if (masterSocket == -1) {
		return 1;
	}
	char* slave = broadcastListen(port);
	printf("%s\n",slave);
	char msg[100];
	printf("Message:  ");
	scanf("%s", msg);
	int len = strlen(msg);
	msg[len++] = '\0';
	sendMsg(masterSocket, slave, port, msg, strlen(msg));
	return 0;
}



/*
int main() {
	int port = 20001;
	int sock = createSocket();
	if (sock == -1) {
		return 1;
	}

	while (1) {
		char msg[100];
		printf("Message:  ");
		scanf("%s", msg);
		int len = strlen(msg);
		msg[len++] = '\0';

		char* ip = "#.#.#.255";

		sendMsg(sock, ip, port, msg, len);

	}
	close(sock);
}*/