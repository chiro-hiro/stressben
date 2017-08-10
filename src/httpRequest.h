#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <iostream>
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

    void push(const char *fName, string fValue);
    void push(const char *fName, const char *fValue);
    void push(char *fName, char *fValue);

    bool eraseField(const char *fName);
    bool eraseField(char *fName);
    bool eraseField(string fName);

    bool eraseValue(const char *fName);
    bool eraseValue(char *fName);
    bool eraseValue(string fName);

    char *get();
    ~httpRequest();
};

#endif /* HTTP_REQUEST_H */