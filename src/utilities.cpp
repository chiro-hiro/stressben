#include "utilities.h"

unsigned int
nanoTime ()
{
  struct timespec ts;
  // clock_gettime(CLOCK_MONOTONIC, &ts); // Works on FreeBSD
  clock_gettime (CLOCK_REALTIME, &ts); // Works on Linux
  return ts.tv_nsec;
}