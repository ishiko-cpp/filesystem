/*
    Copyright (c) 2017-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "Utilities.h"
#include <boost/filesystem.hpp>

namespace Ishiko
{
namespace FileSystem
{

size_t ReadFile(const char* filename, char* buffer, size_t bufferSize, Error& error)
{
    size_t result = 0;

    try
    {
        size_t filesize = boost::filesystem::file_size(filename);
        if (filesize <= bufferSize)
        {
            FILE* file = fopen(filename, "rb");
            if (file)
            {
                result = fread(buffer, 1, filesize, file);
                fclose(file);
            }
        }
        else
        {
            result = filesize;
            error.fail(-2);
        }
    }
    catch (...)
    {
        error.fail(-1);
    }

    return result;
}

}
}
