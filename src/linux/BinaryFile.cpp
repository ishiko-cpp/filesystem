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
    result.m_file_descriptor = open(path.c_str(), O_CREAT | O_EXCL, S_IRUSR | S_IWUSR);
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

void BinaryFile::close()
{
    if (m_file_descriptor != -1)
    {
        ::close(m_file_descriptor);
        m_file_descriptor = -1;
    }
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
