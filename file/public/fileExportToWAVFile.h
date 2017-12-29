/*
    Copyright 2017 Krzysztof Karbowiak
*/

#ifndef FILE_EXPORT_TO_WAV_FILE_H__DDK
#define FILE_EXPORT_TO_WAV_FILE_H__DDK

#include <string>
#include <vector>

namespace wav { struct Format; }

namespace file
{
    bool exportToWAVFile(std::string const & file_name, wav::Format const & format, std::vector<double> const & samples);
}

#endif /* FILE_EXPORT_TO_WAV_FILE_H__DDK */

