char* broadcastListen(int port);
void master_init();
void sendMsg(int sock, char* ip, int port, char* msg, int len);
int createSocket();