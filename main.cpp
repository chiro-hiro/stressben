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
#include <fstream>
#include <signal.h>
#include <time.h>
#include <vector>
#include "tcpClient.h" 
#include "threadPool.h"

using namespace std;


/* Global sock address in*/
struct sockaddr_in serv_addr;
struct hostent *server;

/* Configuration */
char remoteHost[] = "www.google.com";
ushort remotePort = 80;
vector<string> queries;

/* Terminator */
bool terminated = false;

/* Thread MUTEX */
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

unsigned int
nanotime ()
{
  struct timespec ts;
  // clock_gettime(CLOCK_MONOTONIC, &ts); // Works on FreeBSD
  clock_gettime (CLOCK_REALTIME, &ts); // Works on Linux
  return ts.tv_nsec;
}

void*
commonBenchW (void *dataPtr)
{
  tcpClient myClient;
  unsigned int startTime, endTime;
  //string data = "GET "
  while (!terminated)
    {
      pthread_mutex_lock (&mutex1);
      startTime = nanotime ();
      //----------------------
      myClient.open ();
      myClient.connect (serv_addr);
      myClient.close ();
      //----------------------
      counter++;
      endTime = nanotime ();
      cout << (double) (endTime - startTime) / 1000000 << " ms" << endl;
      pthread_mutex_unlock (&mutex1);
      usleep (100000);
    }
}

void
commonBench ()
{
  //Create multiply thread
  threadPool myThread;
  myThread.create (commonBenchW);
  myThread.join ();
}

void
eventHandler (int signal)
{
  //Wait for it
  cout << "\nDude we are falling...\n";
  terminated = true;
}

/* Just common thing */
int
main (int argc, char *argv[])
{
  string curLine;
  ifstream fileRead;

  //Dream catcher, Ahihi
  signal (SIGINT, eventHandler);

  //Resolve host name
  server = gethostbyname (remoteHost);
  memset (&serv_addr, 0x0, sizeof (serv_addr));
  serv_addr.sin_family = AF_INET;
  memcpy (&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  serv_addr.sin_port = htons (remotePort);

  //Read queries
  fileRead.open ("queries.txt", ios::in | ios::app);
  if (fileRead.is_open ())
    {
      while (getline (fileRead, curLine))
        {
          queries.push_back (curLine);
        }
      fileRead.close ();
    }
  commonBench ();
  //The death coming
  while (!terminated)
    {
      usleep (1000000);
    }
  return 0;
}
