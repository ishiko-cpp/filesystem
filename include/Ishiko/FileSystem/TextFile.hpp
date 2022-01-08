/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_TEXTFILE_HPP_
#define _ISHIKO_CPP_FILESYSTEM_TEXTFILE_HPP_

#include <Ishiko/Errors.hpp>
#include <fstream>
#include <string>

namespace Ishiko
{
namespace FileSystem
{

class TextFile
{
public:
    TextFile() = default;
    void create(const std::string& path, Error& error);
    void open(const std::string& path, Error& error);

    std::string readLine(Error& error);
    std::vector<std::string> readAllLines(Error& error);
    template<typename Callable> void forEachLine(Callable&& callback, bool recursive);

    void write(const char* str);
    void writeLine(const char* str);

private:
    std::fstream m_file;
};

template<typename Callable>
void TextFile::forEachLine(Callable&& callback, bool recursive)
{
}

}
}

#endif
