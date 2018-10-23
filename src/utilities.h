#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

unsigned int nanoTime();

vector<string> readFile(string fileName);

#endif /* UTILITIES_H */
