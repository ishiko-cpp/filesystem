/*
    Copyright (c) 2017-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_UTILITIES_H_
#define _ISHIKO_CPP_FILESYSTEM_UTILITIES_H_

#include <boost/filesystem/path.hpp>
#include <Ishiko/BasePlatform.h>
#include <Ishiko/Errors.hpp>
#include <cstddef>
#include <string>
#include <vector>

namespace Ishiko
{
namespace FileSystem
{
    
bool Exists(const char* path);
bool Exists(const std::string& path);
bool Exists(const boost::filesystem::path& path);
size_t GetFileSize(const char* path, Error& error);
bool IsDirectory(const char* path, Error& error);
bool IsEmpty(const char* path, Error& error);
void ToAbsolutePath(const char* path, std::string& absolutePath);
void ToAbsolutePath(const std::string& path, std::string& absolutePath);
void CreateEmptyFile(const std::string& path, Error& error);
void CreateEmptyFile(const boost::filesystem::path& path, Error& error);
size_t ReadFile(const char* filename, char* buffer, size_t bufferSize, Error& error);
std::string ReadFile(const char* filename, Error& error);
std::string ReadFile(const boost::filesystem::path& path, Error& error);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
void GetVolumeList(std::vector<std::string>& volumeNames, Error& error);
#endif

}
}

#include "linkoptions.h"

#endif
