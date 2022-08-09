/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "TextFile.hpp"
#include "Utilities.hpp"
#include <Ishiko/IO.hpp>

using namespace boost::filesystem;

namespace Ishiko
{

void TextFile::create(const boost::filesystem::path& path, Error& error)
{
    create(path.string(), error);
}

void TextFile::create(const std::string& path, Error& error)
{
    // TODO: use lower level file functions to make this more robust
    if (!FileSystem::Exists(path))
    {
        m_file.open(path, std::ios::out);
        FailIfCreateFileError(m_file, path, __FILE__, __LINE__, error);
        m_file.close();
        m_file.open(path);
        FailIfCreateFileError(m_file, path, __FILE__, __LINE__, error);
    }
    else
    {
        Fail(FileSystemErrorCategory::Value::already_exists, std::string("path \'") + path + "\' already exists",
            __FILE__, __LINE__, error);
    }
}

void TextFile::open(const boost::filesystem::path& path, Error& error)
{
    open(path.string(), error);
}

void TextFile::open(const std::string& path, Error& error)
{
    m_file.open(path);
    FailIfOpenFileError(m_file, path, __FILE__, __LINE__, error);
}

void TextFile::close()
{
    m_file.close();
}

std::string TextFile::readLine(Error& error)
{
    std::string result;
    
    std::getline(m_file, result);
    if (m_file.fail())
    {
        if (m_file.eof())
        {
            Fail(FileSystemErrorCategory::Value::end_of_file, error);
        }
        else
        {
            Fail(FileSystemErrorCategory::Value::read_error, error);
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
            if (readError.condition() != FileSystemErrorCategory::Value::end_of_file)
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

// TODO: test
void TextFile::write(const char* str, size_t size)
{
    // TODO: error handling
    m_file.write(str, size);
}

// TODO: test
void TextFile::write(const std::string& str)
{
    m_file.write(str.c_str(), str.size());
}

void TextFile::writeLine(const char* str)
{
    // TODO: error handling
    m_file << str << std::endl;
}

// TODO: test
void TextFile::writeLine(const char* str, size_t size)
{
    // TODO: error handling
    m_file.write(str, size);
    m_file << std::endl;
}

// TODO: test
void TextFile::writeLine(const std::string& str)
{
    // TODO: error handling
    m_file.write(str.c_str(), str.size());
    m_file << std::endl;
}

void TextFile::flush()
{
    m_file.flush();
}

}
