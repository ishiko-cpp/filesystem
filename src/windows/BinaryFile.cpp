/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "BinaryFile.hpp"
#include "FileSystemErrorCategory.hpp"

using namespace Ishiko;

BinaryFile::BinaryFile(BinaryFile&& other)
{
    std::swap(m_file_handle, other.m_file_handle);
}

BinaryFile::~BinaryFile()
{
    if (m_file_handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_file_handle);
    }
}

BinaryFile& BinaryFile::operator=(BinaryFile&& other)
{
    std::swap(m_file_handle, other.m_file_handle);
    return *this;
}

BinaryFile BinaryFile::Create(const boost::filesystem::path& path, Ishiko::Error& error)
{
    return Create(path.string(), error);
}

BinaryFile BinaryFile::Create(const std::string& path, Ishiko::Error& error)
{
    BinaryFile result;

    result.m_file_handle = CreateFileA(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL, NULL);
    if (result.m_file_handle == INVALID_HANDLE_VALUE)
    {
        DWORD last_error = GetLastError();
        if (last_error == ERROR_FILE_EXISTS)
        {
            Fail(FileSystemErrorCategory::Value::already_exists, std::string("path \'") + path + "\' already exists",
                __FILE__, __LINE__, error);
        }
        else
        {
            Fail(FileSystemErrorCategory::Value::generic_error, std::string("path \'") + path + "\' already exists",
                __FILE__, __LINE__, error);
        }
    }

    return result;
}

void BinaryFile::close()
{
    if (m_file_handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_file_handle);
        m_file_handle = INVALID_HANDLE_VALUE;
    }
}

void BinaryFile::write(const char* buffer, size_t length, Error& error)
{
    DWORD bytes_written;
    BOOL succeedded = WriteFile(m_file_handle, buffer, length, &bytes_written, NULL);
    if (!succeedded)
    {
        // TODO: more informative error
        Fail(FileSystemErrorCategory::Value::generic_error, "", __FILE__, __LINE__, error);
    }
}

void BinaryFile::flush()
{
    FlushFileBuffers(m_file_handle);
}
