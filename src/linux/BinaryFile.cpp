/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "BinaryFile.hpp"
#include "FileSystemErrorCategory.hpp"
#include <fcntl.h>

using namespace Ishiko;

BinaryFile::BinaryFile(BinaryFile&& other)
{
    std::swap(m_file_descriptor, other.m_file_descriptor);
}

BinaryFile::~BinaryFile()
{
    if (m_file_descriptor != -1)
    {
        ::close(m_file_descriptor);
    }
}

BinaryFile BinaryFile::Create(const boost::filesystem::path& path, Error& error)
{
    return Create(path.string(), error);
}

BinaryFile BinaryFile::Create(const std::string& path, Error& error)
{
    BinaryFile result;

    // TODO: allow user to configure mask
    result.m_file_descriptor = open(path.c_str(), O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);
    if (result.m_file_descriptor == -1)
    {
        if (errno == EEXIST)
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

BinaryFile BinaryFile::Open(const boost::filesystem::path& path, Error& error)
{
    return Open(path.string(), error);
}

BinaryFile BinaryFile::Open(const std::string& path, Error& error)
{
    BinaryFile result;

    result.m_file_descriptor = open(path.c_str(), O_RDWR);
    if (result.m_file_descriptor == -1)
    {
        if (errno == ENOENT)
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

    return result;
}

void BinaryFile::close()
{
    if (m_file_descriptor != -1)
    {
        ::close(m_file_descriptor);
        m_file_descriptor = -1;
    }
}

size_t BinaryFile::size()
{
    return lseek(m_file_descriptor, 0, SEEK_END);
}

void BinaryFile::resize(size_t new_size)
{
    ftruncate(m_file_descriptor, new_size);
}

size_t BinaryFile::getFilePointer()
{
    return lseek(m_file_descriptor, 0, SEEK_CUR);
}

void BinaryFile::setFilePointer(size_t pos)
{
    lseek(m_file_descriptor, pos, SEEK_SET);
}

void BinaryFile::write(const char* buffer, size_t length, Error& error)
{
    // TODO: error handling
    ::write(m_file_descriptor, buffer, length);
}

void BinaryFile::flush()
{
    fsync(m_file_descriptor);
}
