/*
    Copyright (c) 2017-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_UTILITIES_HPP_
#define _ISHIKO_CPP_FILESYSTEM_UTILITIES_HPP_

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
size_t GetFileSize(const char* path);
size_t GetFileSize(const char* path, Error& error) noexcept;
bool IsDirectory(const char* path, Error& error) noexcept;
bool IsEmpty(const char* path, Error& error) noexcept;
void ToAbsolutePath(const char* path, std::string& absolutePath);
void ToAbsolutePath(const std::string& path, std::string& absolutePath);
void CreateEmptyFile(const std::string& path, Error& error) noexcept;
void CreateEmptyFile(const boost::filesystem::path& path, Error& error) noexcept;

// This function should simply be called CopyFile. Unfortunately the Windows system header define a macro named
// CopyFile that interferes. Since it is a macro namespacing doesn't solve the issue. The issue it creates is also
// obscure to diagnose so it was simpler to avoid the clash entirely.
void CopySingleFile(const boost::filesystem::path& sourcePath, const boost::filesystem::path& targetPath,
    Error& error) noexcept;
size_t ReadFile(const char* filename, char* buffer, size_t bufferSize, Error& error) noexcept;
std::string ReadFile(const char* filename);
std::string ReadFile(const char* filename, Error& error) noexcept;
std::string ReadFile(const boost::filesystem::path& path);
std::string ReadFile(const boost::filesystem::path& path, Error& error) noexcept;
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
void GetVolumeList(std::vector<std::string>& volumeNames, Error& error) noexcept;
#endif

}
}

#endif
