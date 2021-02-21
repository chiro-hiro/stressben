#include "httpRequest.h"

httpRequest::httpRequest()
{
    this->method = "GET";
    this->uri = "/";
    this->version = "1.1";
}

void httpRequest::push(string fName, string fValue)
{
    this->field.push_back(fName);
    this->value.push_back(fValue);
}

bool httpRequest::eraseField(string fName)
{
    for (size_t i = 0; i < this->field.size(); i++)
    {
        if (this->field[i].find(fName) != string::npos)
        {
            this->field.erase(field.begin() + i);
            this->value.erase(value.begin() + i);
            return true;
        }
    }
    return false;
}

bool httpRequest::eraseValue(string fValue)
{
    for (size_t i = 0; i < this->value.size(); i++)
    {
        if (this->value[i].find(fValue) != string::npos)
        {
            this->field.erase(field.begin() + i);
            this->value.erase(value.begin() + i);
            return true;
        }
    }
    return false;
}

string httpRequest::get()
{
    stringstream buf;
    size_t index;
    buf << this->method << " " << uri << " HTTP/" << version << eOL;

    if (body.length() > 0)
    {
        push(string("Content-Length"), std::to_string(body.length()));
    }
    for (size_t i = 0; i < field.size(); i++)
    {
        buf << this->field[i] << ": " << this->value[i] << eOL;
    }
    buf << eOL;
    buf << body;
    return buf.str();
}

httpRequest::~httpRequest()
{
    this->value.clear();
    this->value.shrink_to_fit();
    this->field.clear();
    this->field.shrink_to_fit();
}