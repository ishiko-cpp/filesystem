/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "BinaryFile.hpp"
#include "FileSystemErrorCategory.hpp"
#include "Utilities.hpp"

using namespace boost::filesystem;
using namespace std;

namespace Ishiko
{

BinaryFile BinaryFile::Create(const path& path, Error& error)
{
    return Create(path.string(), error);
}

BinaryFile BinaryFile::Create(const string& path, Error& error)
{
    BinaryFile result;

    // TODO: use lower level file functions to make this more robust
    if (!FileSystem::Exists(path))
    {
        result.m_file.open(path, ios::out | ios::binary);
        FailIfCreateFileError(error, result.m_file, path, __FILE__, __LINE__);
        result.m_file.close();
        result.m_file.open(path, ios_base::in | ios_base::out | ios::binary);
        FailIfCreateFileError(error, result.m_file, path, __FILE__, __LINE__);
    }
    else
    {
        Fail(error, FileSystemErrorCategory::Value::alreadyExists, string("path \'") + path + "\' already exists",
            __FILE__, __LINE__);
    }

    return result;
}

void BinaryFile::close()
{
    m_file.close();
}

void BinaryFile::write(const char* buffer, size_t length)
{
    // TODO: error handling
    m_file.write(buffer, length);
}

void BinaryFile::flush()
{
    m_file.flush();
}

}
