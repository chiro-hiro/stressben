/*
MIT License

Copyright (c) 2016 Dũng Trần <tad88.dev@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#ifndef TCPCLIENT_H
#define TCPCLIENT_H

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

