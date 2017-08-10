#include "httpRequest.h"

httpRequest::httpRequest()
{
    method = "GET";
    uri = "/";
    version = "1.1";
}

void httpRequest::push(const char *fName, string fValue)
{
    field.push_back(string(fName));
    value.push_back(fValue);
}

void httpRequest::push(const char *fName, const char *fValue)
{
    httpRequest::push((char *)fName, (char *)fValue);
}

void httpRequest::push(char *fName, char *fValue)
{
    field.push_back(string(fName));
    value.push_back(string(fValue));
}

bool httpRequest::eraseField(const char *fName)
{
    return eraseField(string(fName));
}

bool httpRequest::eraseField(char *fName)
{
    return eraseField(string(fName));
}

bool httpRequest::eraseField(string fName)
{
    for (size_t i = 0; i < field.size(); i++)
    {
        if (field[i].find(fName) != string::npos)
        {
            field.erase(field.begin() + i);
            value.erase(value.begin() + i);
            return true;
        }
    }
    return false;
}

bool httpRequest::eraseValue(const char *fValue)
{
    return eraseValue(string(fValue));
}

bool httpRequest::eraseValue(char *fValue)
{
    return eraseValue(string(fValue));
}

bool httpRequest::eraseValue(string fValue)
{
    for (size_t i = 0; i < value.size(); i++)
    {
        if (value[i].find(fValue) != string::npos)
        {
            field.erase(field.begin() + i);
            value.erase(value.begin() + i);
            return true;
        }
    }
    return false;
}

char *httpRequest::get()
{
    string tmp;
    size_t index;
    tmp += method;
    tmp += " ";
    tmp += uri;
    tmp += " HTTP/";
    tmp += version;
    tmp += eOL;
    if (body.length() > 0)
    {
        push("Content-Length", std::to_string(body.length()));
    }
    for (size_t i = 0; i < field.size(); i++)
    {
        tmp += field[i];
        tmp += ": ";
        tmp += value[i];
        tmp += eOL;
    }
    tmp += eOL;
    tmp += body;
    return (char *)tmp.c_str();
}

httpRequest::~httpRequest()
{
}