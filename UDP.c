/*byte[1024]          buffer
InternetAddress     fromWho
recvSock = new Socket(udp)
recvSock.bind(addr)         // same addr as sender
loop {
    buffer.clear

    // fromWho will be modified by ref here. Or it's a return value. Depends.
    recvSock.receiveFrom(buffer, ref fromWho)
    if(fromWho.IP != localIP){      // check we are not receiving from ourselves
        // do stuff with buffer
    }
}*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFFERSIZE 1024

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
int main() {
	int sock = createSocket();
	if (sock == -1) {
		return 1;
	}

	while (1) {
		char
	}
	return 0;
}
