#ifndef RANDOMIZE_H
#define RANDOMIZE_H
#define RANDOMIZE_BUFFER_LEN 100

#include <stdlib.h>
#include <iostream>

using namespace std;

class randomize {
public:
    randomize();
    long getRandomNumber(size_t min, size_t max);
    string getRandomCookie(size_t min, size_t max);
    string getRandomPath(size_t min, size_t max);
    string getRandomParam(size_t min, size_t max);
    string getRandomValue(size_t min, size_t max);
    ~randomize();
};

#endif /* RANDOMIZE_H */