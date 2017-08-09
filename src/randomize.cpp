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

#include "randomzie.h"
#include "utilities.h"

#define RANDOMIZE_MIN_COOKIE_LEN 5
#define RANDOMIZE_MAX_COOKIE_LEN 15
#define RANDOMIZE_MIN_COOKIE_VALEN 10
#define RANDOMIZE_MAX_COOKIE_VALEN 20
#define RANDOMIZE_MIN_PATH_LEN 5
#define RANDOMIZE_MAX_PATH_LEN 10

randomize::randomize ()
{
  srand (nanoTime ());
}

long
randomize::getRandomNumber (size_t min, size_t max)
{
  return min + rand () % (max - min + 1);
}

string
randomize::getRandomCookie (size_t min, size_t max)
{
  string buffer ("");
  max = randomize::getRandomNumber (min, max);
  for (size_t len = 0; len < max; len++)
    {
      buffer += randomize::getRandomParam (RANDOMIZE_MIN_COOKIE_LEN, RANDOMIZE_MAX_COOKIE_LEN);
      buffer += "=";
      buffer += randomize::getRandomParam (RANDOMIZE_MIN_COOKIE_VALEN, RANDOMIZE_MAX_COOKIE_VALEN);
      buffer += "; ";
    }
  return buffer;
}

string
randomize::getRandomPath(size_t min, size_t max)
{
  string buffer ("");
  max = randomize::getRandomNumber (min, max);
  for (size_t len = 0; len < max; len++)
    {
      buffer += "/";
      buffer += randomize::getRandomParam (RANDOMIZE_MIN_PATH_LEN, RANDOMIZE_MAX_PATH_LEN);
    }
  return buffer;
}

string
randomize::getRandomParam (size_t min, size_t max)
{
  string buffer ("");
  max = randomize::getRandomNumber (min, max);
  for (size_t len = 0; len < max; len++)
    {
      buffer += (char) randomize::getRandomNumber ('a', 'z');
    }
  return buffer;
}

string
randomize::getRandomValue (size_t min, size_t max)
{
  char mapping[] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F',
  };
  string buffer ("");
  max = randomize::getRandomNumber (min, max);
  for (size_t len = 0; len < max; len++)
    {
      buffer += "%";
      buffer += mapping[randomize::getRandomNumber (0, 15)];
      buffer += mapping[randomize::getRandomNumber (0, 15)];
    }
  return buffer;
}

randomize::~randomize () { }