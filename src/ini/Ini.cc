#include "Ini.hh"

#include <glog/logging.h>

Ini::Ini()
{
    if (this->reader.ParseError() != 0)
    {
        LOG(ERROR) << "Can't load config.ini";
    }
}

Ini::~Ini()
{
}
