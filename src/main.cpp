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
#include <vector>
#include "tcpClient.h" 
#include "threadPool.h"
#include "utilities.h"
#include "randomzie.h"

using namespace std;

/* Global sock address in*/
struct sockaddr_in serv_addr;
struct hostent *server;

/* Configuration */
char remoteHost[] = "139.162.25.101";
ushort remotePort = 3003;
vector<string> queries;

/* Terminator */
bool terminated = false;

/* Thread MUTEX */
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;

/* Common bench */
void*commonBenchW (void *dataPtr);
void commonBench ();

/* */
void*undefineBenchW (void *dataPtr);
void undefinedBench ();

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
  randomize test;
  cout << test.getRandomPath (50, 200) << endl;
  cout << test.getRandomCookie (200, 500) << endl;
  cout << test.getRandomNumber (1, 255) << endl;
  cout << test.getRandomParam (10, 20) << endl;
  cout << test.getRandomValue (15, 50) << endl;
  return 0;
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

void*
commonBenchW (void *dataPtr)
{
  tcpClient myClient;
  unsigned int startTime, endTime;
  srand (nanoTime ());
  string data = "GET ";
  char buffer[1024];
  while (!terminated)
    {
      data += queries[rand () % queries.size ()];
      data += " HTTP/1.1\n";
      data += "Host: ";
      data += remoteHost;
      data += "\n\n";
      startTime = nanoTime ();
      //----------------------
      myClient.open ();
      myClient.connect (serv_addr);
      myClient.send ((void*) data.c_str (), (size_t) data.length ());
      myClient.recv (buffer, 1023);
      buffer[1023] = 0x0;
      //cout << data << "\n";
      //cout << buffer << "\n";
      myClient.close ();
      //----------------------

      endTime = nanoTime ();
      pthread_mutex_lock (&mutex1);
      cout << (double) (endTime - startTime) / 1000000 << endl;
      counter++;
      pthread_mutex_unlock (&mutex1);
      usleep (100000);
    }
  cout << "Terminated...\n";
}

void
commonBench ()
{
  //Create multiply thread
  threadPool myThread;
  myThread.create (commonBenchW);
  myThread.join ();
}

void*
undefinedBenchW (void *dataPtr)
{
  tcpClient myClient;
  unsigned int startTime, endTime;
  randomize rndSrc;
  srand (nanoTime ());
  string data = "GET ";
  char buffer[1024];
  while (!terminated)
    {
      data += rndSrc.getRandomPath (50, 100);
      data += " HTTP/1.1\n";
      data += "Host: ";
      data += remoteHost;
      data += "\n";
      data += "Cookie: ";
      data += rndSrc.getRandomCookie (200, 500);
      data += "\n\n";
      startTime = nanoTime ();
      //----------------------
      myClient.open ();
      myClient.connect (serv_addr);
      myClient.send ((void*) data.c_str (), (size_t) data.length ());
      myClient.recv (buffer, 1023);
      buffer[1023] = 0x0;
      //cout << data << "\n";
      //cout << buffer << "\n";
      myClient.close ();
      //----------------------

      endTime = nanoTime ();
      pthread_mutex_lock (&mutex1);
      cout << (double) (endTime - startTime) / 1000000 << endl;
      counter++;
      pthread_mutex_unlock (&mutex1);
      usleep (100000);
    }
  cout << "Terminated...\n";
}

void
undefinedBench ()
{
  //Create multiply thread
  threadPool myThread;
  myThread.create (undefinedBenchW);
  myThread.join ();
}