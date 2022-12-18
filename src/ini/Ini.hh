#ifndef _FRAMEWORK_INI_HEADER_
#define _FRAMEWORK_INI_HEADER_

#include <INIReader.h>

#include "../comm/Singleton.hh"

class Ini : public Singleton<Ini>
{
public:
    Ini();
    ~Ini();

    INIReader &GetReader();

private:
    INIReader reader = INIReader("../resources/config.ini");
};

#endif