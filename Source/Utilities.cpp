/*
    Copyright (c) 2017-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "Utilities.h"
#include "ErrorCategory.h"
#include <boost/filesystem/operations.hpp>

namespace Ishiko
{
namespace FileSystem
{

bool Exists(const char* path)
{
    return boost::filesystem::exists(path);
}

bool IsDirectory(const char* path, Error& error)
{
    try
    {
        if (Exists(path))
        {
            return boost::filesystem::is_directory(path);
        }
        else
        {
            Fail(error, ErrorCategory::eNotFound);
            return false;
        }
    }
    catch (...)
    {
        // According to the Boost documentation boost::filesystem::is_directory throws when the path doesn't exist but
        // it doesn't seem to do that in our tests.
        Fail(error, ErrorCategory::eNotFound);
        return false;
    }
}

bool IsEmpty(const char* path, Error& error)
{
    try
    {
        return boost::filesystem::is_empty(path);
    }
    catch (...)
    {
        Fail(error, ErrorCategory::eNotFound);
        return false;
    }
}

void ToAbsolutePath(const char* path, std::string& absolutePath)
{
    absolutePath = boost::filesystem::absolute(path).string();
}

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
            Fail(error, ErrorCategory::eBufferOverflow);
        }
    }
    catch (...)
    {
        Fail(error, ErrorCategory::eGeneric);
    }

    return result;
}

}
}
