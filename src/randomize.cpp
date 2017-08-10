#include "randomzie.h"
#include "utilities.h"

#define RANDOMIZE_MIN_COOKIE_LEN 5
#define RANDOMIZE_MAX_COOKIE_LEN 15
#define RANDOMIZE_MIN_COOKIE_VALEN 10
#define RANDOMIZE_MAX_COOKIE_VALEN 20
#define RANDOMIZE_MIN_PATH_LEN 5
#define RANDOMIZE_MAX_PATH_LEN 10

randomize::randomize()
{
  srand(nanoTime());
}

long randomize::getRandomNumber(size_t min, size_t max)
{
  return min + rand() % (max - min + 1);
}

string
randomize::getRandomCookie(size_t min, size_t max)
{
  string buffer("");
  max = randomize::getRandomNumber(min, max);
  for (size_t len = 0; len < max; len++)
  {
    buffer += randomize::getRandomParam(RANDOMIZE_MIN_COOKIE_LEN, RANDOMIZE_MAX_COOKIE_LEN);
    buffer += "=";
    buffer += randomize::getRandomParam(RANDOMIZE_MIN_COOKIE_VALEN, RANDOMIZE_MAX_COOKIE_VALEN);
    buffer += "; ";
  }
  return buffer;
}

string
randomize::getRandomPath(size_t min, size_t max)
{
  string buffer("");
  max = randomize::getRandomNumber(min, max);
  for (size_t len = 0; len < max; len++)
  {
    buffer += "/";
    buffer += randomize::getRandomParam(RANDOMIZE_MIN_PATH_LEN, RANDOMIZE_MAX_PATH_LEN);
  }
  return buffer;
}

string
randomize::getRandomParam(size_t min, size_t max)
{
  string buffer("");
  max = randomize::getRandomNumber(min, max);
  for (size_t len = 0; len < max; len++)
  {
    buffer += (char)randomize::getRandomNumber('a', 'z');
  }
  return buffer;
}

string
randomize::getRandomValue(size_t min, size_t max)
{
  char mapping[] = {
      '0', '1', '2', '3',
      '4', '5', '6', '7',
      '8', '9', 'A', 'B',
      'C', 'D', 'E', 'F',
  };
  string buffer("");
  max = randomize::getRandomNumber(min, max);
  for (size_t len = 0; len < max; len++)
  {
    buffer += "%";
    buffer += mapping[randomize::getRandomNumber(0, 15)];
    buffer += mapping[randomize::getRandomNumber(0, 15)];
  }
  return buffer;
}

randomize::~randomize() {}