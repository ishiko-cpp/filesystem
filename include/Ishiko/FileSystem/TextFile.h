/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_FILESYSTEM_TEXTFILE_H_
#define _ISHIKO_FILESYSTEM_TEXTFILE_H_

#include <Ishiko/Errors.h>
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

    void write(const char* str);
    void writeLine(const char* str);

private:
    std::fstream m_file;
};

}
}

#endif
