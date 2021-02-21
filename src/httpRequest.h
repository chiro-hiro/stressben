#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define eOL "\r\n";

class httpRequest
{
private:
  vector<string> field;
  vector<string> value;

public:
  string method;
  string uri;
  string version;
  string body;
  httpRequest();

  void push(string fName, string fValue);

  bool eraseField(string fName);

  bool eraseValue(string fValue);

  string get();
  ~httpRequest();
};
