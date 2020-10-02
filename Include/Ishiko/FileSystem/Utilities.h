/*
    Copyright (c) 2017-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_FILESYSTEM_UTILITIES_H_
#define _ISHIKO_FILESYSTEM_UTILITIES_H_

#include "Ishiko/Errors/Error.h"
#include <cstddef>

namespace Ishiko
{
namespace FileSystem
{
    
bool Exists(const char* path);
bool IsDirectory(const char* path, Error& error);
bool IsEmpty(const char* path, Error& error);
size_t ReadFile(const char* filename, char* buffer, size_t bufferSize, Error& error);

}
}

#include "linkoptions.h"

#endif
