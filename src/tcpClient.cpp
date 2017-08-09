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

#include "tcpClient.h"

tcpClient::tcpClient () : status (TCPCLIENT_SOCKET_NEW), fd (0) { }

void
tcpClient::open ()
{
  fd = socket (AF_INET, SOCK_STREAM, 0);
  status = (fd < 0) ? TCPCLIENT_SOCKET_ERROR : TCPCLIENT_SOCKET_CONNECTING;
}

void
tcpClient::connect (struct sockaddr_in serv_addr)
{
  status = ::connect (fd, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0 ? TCPCLIENT_SOCKET_ERROR : TCPCLIENT_SOCKET_CONNECTED;
}

size_t
tcpClient::send (void *data, size_t size)
{
  if (status == TCPCLIENT_SOCKET_CONNECTED)
    {
      return write (fd, data, size);
    }

  return -1;
}

size_t
tcpClient::recv (void *data, size_t size)
{
  if (status == TCPCLIENT_SOCKET_CONNECTED)
    {
      return read (fd, data, size);
    }
  return -1;
}

void
tcpClient::close ()
{
  status = ::close (fd) == 0 ? TCPCLIENT_SOCKET_ERROR : TCPCLIENT_SOCKET_CLOSED;
}

socketStatus
tcpClient::getStatus ()
{
  return status;
}

void
tcpClient::setStatus (socketStatus newStatus)
{
  status = newStatus;
}

tcpClient::~tcpClient () { }