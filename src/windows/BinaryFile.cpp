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

BinaryFile BinaryFile::Create(const boost::filesystem::path& path, Error& error)
{
    return Create(path.string(), error);
}

BinaryFile BinaryFile::Create(const std::string& path, Error& error)
{
    BinaryFile result;
    result.create(path.c_str(), error);
    return result;
}

BinaryFile BinaryFile::Open(const boost::filesystem::path& path, Error& error)
{
    return Open(path.string(), error);
}

BinaryFile BinaryFile::Open(const std::string& path, Error& error)
{
    BinaryFile result;
    result.open(path.c_str(), error);
    return result;
}

void BinaryFile::create(const boost::filesystem::path& path, Error& error)
{
    create(path.c_str(), error);
}

void BinaryFile::create(const char* path, Error& error)
{
    m_file_handle = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (m_file_handle == INVALID_HANDLE_VALUE)
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
}

void BinaryFile::create(const wchar_t* path, Error& error)
{
    m_file_handle = CreateFileW(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    if (m_file_handle == INVALID_HANDLE_VALUE)
    {
        DWORD last_error = GetLastError();
        if (last_error == ERROR_FILE_EXISTS)
        {
            Fail(FileSystemErrorCategory::Value::already_exists,
                std::wstring(L"path \'") + path + L"\' already exists", __FILE__, __LINE__, error);
        }
        else
        {
            Fail(FileSystemErrorCategory::Value::generic_error, std::wstring(L"path \'") + path + L"\' already exists",
                __FILE__, __LINE__, error);
        }
    }
}

void BinaryFile::open(const boost::filesystem::path& path, Error& error)
{
    open(path.c_str(), error);
}

void BinaryFile::open(const char* path, Error& error)
{
    m_file_handle = CreateFileA(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (m_file_handle == INVALID_HANDLE_VALUE)
    {
        DWORD last_error = GetLastError();
        if (last_error == ERROR_FILE_NOT_FOUND)
        {
            Fail(FileSystemErrorCategory::Value::not_found, std::string("path \'") + path + "\' not found", __FILE__,
                __LINE__, error);
        }
        else
        {
            Fail(FileSystemErrorCategory::Value::generic_error, std::string("path \'") + path + "\' not found",
                __FILE__, __LINE__, error);
        }
    }
}

void BinaryFile::open(const wchar_t* path, Error& error)
{
    m_file_handle = CreateFileW(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (m_file_handle == INVALID_HANDLE_VALUE)
    {
        DWORD last_error = GetLastError();
        if (last_error == ERROR_FILE_NOT_FOUND)
        {
            Fail(FileSystemErrorCategory::Value::not_found, std::wstring(L"path \'") + path + L"\' not found",
                __FILE__, __LINE__, error);
        }
        else
        {
            Fail(FileSystemErrorCategory::Value::generic_error, std::wstring(L"path \'") + path + L"\' not found",
                __FILE__, __LINE__, error);
        }
    }
}

void BinaryFile::close()
{
    if (m_file_handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(m_file_handle);
        m_file_handle = INVALID_HANDLE_VALUE;
    }
}

size_t BinaryFile::size()
{
    LARGE_INTEGER result;
    GetFileSizeEx(m_file_handle, &result);
    return result.QuadPart;
}

void BinaryFile::resize(size_t new_size)
{
    size_t previous_file_pointer = getFilePointer();
    LARGE_INTEGER offset;
    offset.QuadPart = new_size;
    SetFilePointerEx(m_file_handle, offset, NULL, FILE_BEGIN);
    SetEndOfFile(m_file_handle);
    setFilePointer(previous_file_pointer);
}

size_t BinaryFile::getFilePointer()
{
    LARGE_INTEGER offset;
    offset.QuadPart = 0;
    LARGE_INTEGER result;
    SetFilePointerEx(m_file_handle, offset, &result, FILE_CURRENT);
    return result.QuadPart;
}

void BinaryFile::setFilePointer(size_t pos)
{
    LARGE_INTEGER offset;
    offset.QuadPart = pos;
    SetFilePointerEx(m_file_handle, offset, NULL, FILE_BEGIN);
}

size_t BinaryFile::read(size_t length, char* buffer, Error& error)
{
    DWORD result;
    // TODO: check return value
    BOOL succeeded = ReadFile(m_file_handle, buffer, length, &result, NULL);
    if (!succeeded)
    {
        // TODO: more informative error
        Fail(FileSystemErrorCategory::Value::generic_error, "", __FILE__, __LINE__, error);
    }
    return result;
}

size_t BinaryFile::read(size_t pos, size_t length, char* buffer, Error& error)
{
    DWORD result;
    OVERLAPPED overlapped;
    memset(&overlapped, 0, sizeof(overlapped));
    overlapped.Offset = pos;
    BOOL succeeded = ReadFile(m_file_handle, buffer, length, &result, &overlapped);
    return result;
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

void BinaryFile::write(const char* buffer, size_t pos, size_t length, Error& error)
{
    DWORD bytes_written;
    OVERLAPPED overlapped;
    memset(&overlapped, 0, sizeof(overlapped));
    overlapped.Offset = pos;
    BOOL succeedded = WriteFile(m_file_handle, buffer, length, &bytes_written, &overlapped);
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
