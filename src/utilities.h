#ifndef UTILITIES_H
#define UTILITIES_H

#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

unsigned int
nanoTime();

vector<string>
readFile(string fileName);

#endif /* UTILITIES_H */
