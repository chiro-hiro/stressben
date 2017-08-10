#include "tcpClient.h"

tcpClient::tcpClient() : status(TCPCLIENT_SOCKET_NEW), fd(0) {}

void tcpClient::open()
{
  fd = socket(AF_INET, SOCK_STREAM, 0);
  status = (fd < 0) ? TCPCLIENT_SOCKET_ERROR : TCPCLIENT_SOCKET_CONNECTING;
}

void tcpClient::connect(struct sockaddr_in serv_addr)
{
  status = ::connect(fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 ? TCPCLIENT_SOCKET_ERROR : TCPCLIENT_SOCKET_CONNECTED;
}

size_t
tcpClient::send(void *data, size_t size)
{
  if (status == TCPCLIENT_SOCKET_CONNECTED)
  {
    return write(fd, data, size);
  }

  return -1;
}

size_t
tcpClient::recv(void *data, size_t size)
{
  if (status == TCPCLIENT_SOCKET_CONNECTED)
  {
    return read(fd, data, size);
  }
  return -1;
}

void tcpClient::close()
{
  status = ::close(fd) == 0 ? TCPCLIENT_SOCKET_ERROR : TCPCLIENT_SOCKET_CLOSED;
}

socketStatus
tcpClient::getStatus()
{
  return status;
}

void tcpClient::setStatus(socketStatus newStatus)
{
  status = newStatus;
}

tcpClient::~tcpClient() {}