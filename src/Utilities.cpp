// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "Utilities.hpp"
#include "FileSystemErrorCategory.hpp"
#include <boost/filesystem/operations.hpp>
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
#include <windows.h>
#endif
#include <fstream>

namespace Ishiko
{
namespace FileSystem
{

bool Exists(const char* path)
{
    return boost::filesystem::exists(path);
}

bool Exists(const std::string& path)
{
    return Exists(path.c_str());
}

bool Exists(const boost::filesystem::path& path)
{
    return Exists(path.string());
}

size_t GetFileSize(const char* path)
{
    // TODO: test exceptions, is the boost exception informative enough?
    return boost::filesystem::file_size(path);
}

size_t GetFileSize(const char* path, Error& error) noexcept
{
    try
    {
        return boost::filesystem::file_size(path);
    }
    catch (...)
    {
        Fail(FileSystemErrorCategory::Value::not_found, std::string("path \'") + path + "\' not found", __FILE__,
            __LINE__, error);
        return false;
    }
}

bool IsDirectory(const char* path, Error& error) noexcept
{
    try
    {
        if (Exists(path))
        {
            return boost::filesystem::is_directory(path);
        }
        else
        {
            Fail(FileSystemErrorCategory::Value::not_found, std::string("path \'") + path + "\' not found", __FILE__,
                __LINE__, error);
            return false;
        }
    }
    catch (...)
    {
        // According to the Boost documentation boost::filesystem::is_directory throws when the path doesn't exist but
        // it doesn't seem to do that in our tests.
        Fail(FileSystemErrorCategory::Value::not_found, std::string("path \'") + path + "\' not found", __FILE__,
            __LINE__, error);
        return false;
    }
}

bool IsEmpty(const char* path, Error& error) noexcept
{
    try
    {
        return boost::filesystem::is_empty(path);
    }
    catch (...)
    {
        Fail(FileSystemErrorCategory::Value::not_found, std::string("path \'") + path + "\' not found", __FILE__,
            __LINE__, error);
        return false;
    }
}

void ToAbsolutePath(const char* path, std::string& absolutePath)
{
    absolutePath = boost::filesystem::absolute(path).string();
}

void ToAbsolutePath(const std::string& path, std::string& absolutePath)
{
    absolutePath = boost::filesystem::absolute(path).string();
}

void CreateEmptyFile(const std::string& path, Error& error) noexcept
{
    // TODO: use lower level file functions to make this more robust
    if (!Exists(path))
    {
        std::ofstream file(path);
    }
    else
    {
        Fail(FileSystemErrorCategory::Value::already_exists, std::string("path \'") + path + "\' already exists",
            __FILE__, __LINE__, error);
    }
}

void CreateEmptyFile(const boost::filesystem::path& path, Error& error) noexcept
{
    CreateEmptyFile(path.string(), error);
}


void CopySingleFile(const boost::filesystem::path& sourcePath, const boost::filesystem::path& targetPath) noexcept
{
    boost::system::error_code ec;
    boost::filesystem::copy_file(sourcePath, targetPath, ec);
    if (ec.failed())
    {
        // TODO: interpret error properly
        Throw(FileSystemErrorCategory::Value::generic_error, __FILE__, __LINE__);
    }
}

void CopySingleFile(const boost::filesystem::path& sourcePath, const boost::filesystem::path& targetPath, Error& error) noexcept
{
    boost::system::error_code ec;
    boost::filesystem::copy_file(sourcePath, targetPath, ec);
    if (ec.failed())
    {
        // TODO: interpret error properly
        Fail(FileSystemErrorCategory::Value::generic_error, "", __FILE__, __LINE__, error);
    }
}

size_t ReadFile(const char* filename, char* buffer, size_t bufferSize, Error& error) noexcept
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
            Fail(FileSystemErrorCategory::Value::buffer_overflow, error);
        }
    }
    catch (...)
    {
        Fail(FileSystemErrorCategory::Value::generic_error, std::string("unknown error for path \'") + filename + "\'",
            __FILE__, __LINE__, error);
    }

    return result;
}

std::string ReadFile(const char* filename)
{
    std::string result;
    size_t fileSize = GetFileSize(filename);
    result.resize(fileSize);
    Error error;
    // TODO: robustness, race condition if file change sizes between GetFileSize and ReadFile
    ReadFile(filename, const_cast<char*>(result.data()), fileSize, error);
    ThrowIf(error);
    return result;
}

std::string ReadFile(const char* filename, Error& error) noexcept
{
    std::string result;
    size_t fileSize = GetFileSize(filename, error);
    if (!error)
    {
        result.resize(fileSize);
        // TODO: robustness, race condition if file change sizes between GetFileSize and ReadFile
        ReadFile(filename, const_cast<char*>(result.data()), fileSize, error);
    }
    return result;
}

std::string ReadFile(const boost::filesystem::path& path)
{
    return ReadFile(path.string().c_str());
}

std::string ReadFile(const boost::filesystem::path& path, Error& error) noexcept
{
    return ReadFile(path.string().c_str(), error);
}

#if ISHIKO_OS == ISHIKO_OS_WINDOWS
void GetVolumeList(std::vector<std::string>& volumeNames, Error& error) noexcept
{
    char volumeName[MAX_PATH + 1];
    HANDLE searchHandle = FindFirstVolumeA(volumeName, MAX_PATH + 1);
    if (searchHandle == INVALID_HANDLE_VALUE)
    {
        Fail(FileSystemErrorCategory::Value::generic_error, "", __FILE__, __LINE__, error);
    }
    else
    {
        volumeNames.emplace_back(volumeName);
        while (FindNextVolumeA(searchHandle, volumeName, MAX_PATH + 1))
        {
            volumeNames.emplace_back(volumeName);
        }
        FindVolumeClose(searchHandle);
    }
}
#endif

}
}
