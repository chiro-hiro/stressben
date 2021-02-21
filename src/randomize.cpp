#include <iostream>
#include <sstream>
#include <sys/random.h>
#include "randomzie.h"
#include "utilities.h"

uint32_t randomize::rangeInt(uint32_t min, uint32_t max)
{
    uint32_t bufVal = 0;
    getrandom(&bufVal, sizeof(uint32_t), GRND_NONBLOCK);
    return bufVal % (max - min) + min;
}

string randomize::cookie(uint32_t min, uint32_t max)
{
    stringstream buffer("");
    uint32_t len = randomize::rangeInt(min, max);
    for (uint32_t i = 0; i < len; i++)
    {
        buffer << randomize::paramName(6, 12)
               << "="
               << randomize::paramName(12, 32)
               << "; ";
    }
    return buffer.str();
}

string randomize::queryString(uint32_t min, uint32_t max)
{
    stringstream buffer("");
    uint32_t len = randomize::rangeInt(min, max);
    for (uint32_t i = 0; i < len; i++)
    {
        if (i > 0)
        {
            buffer << "&";
        }
        buffer << randomize::paramName(6, 12)
               << "="
               << randomize::escapedValue(64, 128);
    }
    return buffer.str();
}

string randomize::path(uint32_t min, uint32_t max)
{
    stringstream buffer("");
    uint32_t len = randomize::rangeInt(min, max);
    for (uint32_t i = 0; i < len; i++)
    {
        buffer << "/" << randomize::paramName(4, 12);
    }
    return buffer.str();
}

string randomize::paramName(uint32_t min, uint32_t max)
{
    stringstream buffer("");
    uint32_t len = randomize::rangeInt(min, max);
    uint32_t tick = 0;
    for (uint32_t i = 0; i < len; i++)
    {
        tick = randomize::rangeInt(0, 100);
        if (tick < 40)
        {
            buffer << (char)randomize::rangeInt('a', 'z');
        }
        else if (tick > 60)
        {
            buffer << (char)randomize::rangeInt('A', 'Z');
        }
        else
        {
            buffer << (char)randomize::rangeInt('0', '9');
        }
    }
    return buffer.str();
}

string randomize::escapedValue(uint32_t min, uint32_t max)
{
    stringstream buffer("");
    uint32_t len = randomize::rangeInt(min, max);
    char *buf = new char[len];
    getrandom(buf, len, GRND_NONBLOCK);
    uint32_t charRead = 0;
    for (uint32_t i = 0; i < len; i++)
    {
        charRead = (0xff & buf[i]);
        if ((charRead >= 48 && charRead <= 57) || (charRead >= 65 && charRead <= 90) || (charRead >= 97 && charRead <= 122) || charRead == 64)
        {
            buffer << buf[i];
        }
        else if (charRead == 0)
        {
            buffer << "%20";
        }
        else
        {
            if (charRead <= 0xf)
            {
                buffer << "%0" << hex << charRead;
            }
            else
            {
                buffer << "%" << hex << charRead;
            }
        }
    }
    delete buf;
    return buffer.str();
}

string randomize::json(uint32_t min, uint32_t max)
{
    stringstream buffer("");
    stringstream close("");
    uint32_t len = randomize::rangeInt(min, max);
    for (uint32_t i = 0; i < len; i++)
    {
        buffer << "{\"" << randomize::paramName(6, 12) << "\":";
        close << "}";
    }
    buffer << "1" << close.str();
    return buffer.str();
}
