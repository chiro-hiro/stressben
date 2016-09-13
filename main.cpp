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

#include <iostream>
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include "tcpClient.h" 
#include "threadPool.h"

using namespace std;


unsigned int
nanotime ()
{
  struct timespec ts;
  // clock_gettime(CLOCK_MONOTONIC, &ts); // Works on FreeBSD
  clock_gettime (CLOCK_REALTIME, &ts); // Works on Linux
  return ts.tv_nsec;
}

void *functionCount2(void *dataPtr)
{
  cout << "Thread ID :" << pthread_self () << endl;
  return (NULL);
}


int
main (int argc, char *argv[])
{
  tcpClient myClient;
  threadPool myThread;
  myThread.create (functionCount2);
  myThread.join ();
  int portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char test[] = "GET / HTTP/1.1\nHost: www.google.com\n\n";
  char buffer[256] = {0};
  unsigned int startTime, endTime;
  portno = 80;
  myClient.open ();
  server = gethostbyname ("www.google.com");
  memset (&serv_addr, 0x0, sizeof (serv_addr));
  serv_addr.sin_family = AF_INET;
  memcpy (&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  serv_addr.sin_port = htons (portno);

  startTime = nanotime ();
  myClient.connect (serv_addr);
  myClient.send (test, strlen (test));
  memset (buffer, 0x0, 256);
  n = myClient.recv (buffer, 256);
  puts (buffer);
  
  myClient.close ();
  endTime = nanotime ();
  cout << (double) (endTime - startTime) / 1000000 << " ms" << endl;
  return 0;
}
