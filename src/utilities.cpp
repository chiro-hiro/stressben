#include "utilities.h"

unsigned int
nanoTime()
{
  struct timespec ts;
  // clock_gettime(CLOCK_MONOTONIC, &ts); // Works on FreeBSD
  clock_gettime(CLOCK_REALTIME, &ts); // Works on Linux
  return ts.tv_nsec;
}

vector<string>
readFile(string fileName)
{
  vector<string> myStack;
  ifstream fileRead;
  string curLine;
  fileRead.open(fileName.c_str(), ios::in | ios::app);
  if (fileRead.is_open())
  {
    while (getline(fileRead, curLine))
    {
      myStack.push_back(curLine);
    }
    fileRead.close();
  }
  return myStack;
}