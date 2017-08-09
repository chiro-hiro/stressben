#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

typedef enum {
    TCPCLIENT_SOCKET_NEW = 0,
    TCPCLIENT_SOCKET_OK = 1,
    TCPCLIENT_SOCKET_CONNECTING = 2,
    TCPCLIENT_SOCKET_CONNECTED = 3,
    TCPCLIENT_SOCKET_LOOKUP = 4,
    TCPCLIENT_SOCKET_SEND = 5,
    TCPCLIENT_SOCKET_RECV = 6,
    TCPCLIENT_SOCKET_CLOSING = 7,
    TCPCLIENT_SOCKET_CLOSED = 8,
    TCPCLIENT_SOCKET_UNKNOW = 9,
    TCPCLIENT_SOCKET_ERROR = 10
} socketStatus;

class tcpClient {
private:
    int fd;
    socketStatus status;
public:    
    tcpClient();
    void open();
    void connect(struct sockaddr_in serv_addr);
    size_t send(void *data, size_t size);
    size_t recv(void *data, size_t size);
    void close();
    socketStatus getStatus();
    void setStatus(socketStatus newStatus);
    ~tcpClient();

};

#endif /* TCPCLIENT_H */

