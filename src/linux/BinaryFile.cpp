/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "BinaryFile.hpp"
#include "FileSystemErrorCategory.hpp"
#include "Utilities.hpp"
#include <Ishiko/IO.hpp>

using namespace Ishiko;

BinaryFile BinaryFile::Create(const boost::filesystem::path& path, Error& error)
{
    return Create(path.string(), error);
}

BinaryFile BinaryFile::Create(const std::string& path, Error& error)
{
    BinaryFile result;

    // TODO: use lower level file functions to make this more robust
    if (!FileSystem::Exists(path))
    {
        result.m_file.open(path, std::ios::out | std::ios::binary);
        FailIfCreateFileError(result.m_file, path, __FILE__, __LINE__, error);
        result.m_file.close();
        result.m_file.open(path, std::ios_base::in | std::ios_base::out | std::ios::binary);
        FailIfCreateFileError(result.m_file, path, __FILE__, __LINE__, error);
    }
    else
    {
        Fail(FileSystemErrorCategory::Value::already_exists, std::string("path \'") + path + "\' already exists",
            __FILE__, __LINE__, error);
    }

    return result;
}

void BinaryFile::close()
{
    m_file.close();
}

void BinaryFile::write(const char* buffer, size_t length, Error& error)
{
    // TODO: error handling
    m_file.write(buffer, length);
}

void BinaryFile::flush()
{
    m_file.flush();
}
