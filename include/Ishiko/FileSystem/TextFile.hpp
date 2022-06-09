/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_TEXTFILE_HPP_
#define _ISHIKO_CPP_FILESYSTEM_TEXTFILE_HPP_

#include "FileSystemErrorCategory.hpp"
#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>
#include <fstream>
#include <string>

namespace Ishiko
{

class TextFile
{
public:
    TextFile() = default;
    void create(const boost::filesystem::path& path, Error& error);
    void create(const std::string& path, Error& error);
    void open(const boost::filesystem::path& path, Error& error);
    void open(const std::string& path, Error& error);
    void close();

    std::string readLine(Error& error);
    std::vector<std::string> readAllLines(Error& error);
    template<typename Callable> void forEachLine(Callable&& callback, Error& error);

    void write(const char* str);
    void write(const char* str, size_t size);
    void write(const std::string& str);
    void writeLine(const char* str);
    void writeLine(const char* str, size_t size);
    void writeLine(const std::string& str);
    void flush();

private:
    std::fstream m_file;
};

template<typename Callable>
void TextFile::forEachLine(Callable&& callback, Error& error)
{
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
        callback(line);
    }
}

}

#endif
