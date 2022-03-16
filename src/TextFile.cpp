/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "TextFile.hpp"
#include "Utilities.hpp"

using namespace boost::filesystem;

namespace Ishiko
{
namespace FileSystem
{

void TextFile::create(const boost::filesystem::path& path, Error& error)
{
    create(path.string(), error);
}

void TextFile::create(const std::string& path, Error& error)
{
    // TODO: use lower level file functions to make this more robust
    if (!Exists(path))
    {
        m_file.open(path, std::ios::out);
        FailIfCreateFileError(error, m_file, path, __FILE__, __LINE__);
        m_file.close();
        m_file.open(path);
        FailIfCreateFileError(error, m_file, path, __FILE__, __LINE__);
    }
    else
    {
        Fail(error, FileSystemErrorCategory::Value::alreadyExists, std::string("path \'") + path + "\' already exists",
            __FILE__, __LINE__);
    }
}

void TextFile::open(const boost::filesystem::path& path, Error& error)
{
    open(path.string(), error);
}

void TextFile::open(const std::string& path, Error& error)
{
    m_file.open(path);
    FailIfOpenFileError(error, m_file, path, __FILE__, __LINE__);
}

std::string TextFile::readLine(Error& error)
{
    std::string result;
    
    std::getline(m_file, result);
    if (m_file.fail())
    {
        if (m_file.eof())
        {
            Fail(error, FileSystemErrorCategory::Value::endOfFile);
        }
        else
        {
            Fail(error, FileSystemErrorCategory::Value::readError);
        }
    }

    return result;
}

std::vector<std::string> TextFile::readAllLines(Error& error)
{
    std::vector<std::string> result;

    while (true)
    {
        Error readError;
        std::string line = readLine(readError);
        if (readError)
        {
            if (readError.condition() != FileSystemErrorCategory::Value::endOfFile)
            {
                error.fail(readError);
            }
            break;
        }
        result.push_back(line);
    }

    return result;
}

void TextFile::write(const char* str)
{
    // TODO: error handling
    m_file << str;
}

void TextFile::writeLine(const char* str)
{
    // TODO: error handling
    m_file << str << std::endl;
}

}
}
