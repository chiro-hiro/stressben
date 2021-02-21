#pragma once

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/random.h>

using namespace std;

namespace randomize
{
  uint32_t rangeInt(uint32_t min, uint32_t max);
  string queryString(uint32_t min, uint32_t max);
  string cookie(uint32_t min, uint32_t max);
  string path(uint32_t min, uint32_t max);
  string paramName(uint32_t min, uint32_t max);
  string json(uint32_t min, uint32_t max);
  string escapedValue(uint32_t min, uint32_t max);
};
