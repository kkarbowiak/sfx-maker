/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef APPLICATION_APLICATION_CONFIGURATION_H__DDK
#define APPLICATION_APLICATION_CONFIGURATION_H__DDK

#include <string>

namespace application
{
    struct AppConfiguration
    {
        bool        display_help;
        std::string file_name;
    };
}

#endif /* APPLICATION_APLICATION_CONFIGURATION_H__DDK */

