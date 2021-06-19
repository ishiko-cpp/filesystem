/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
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
    std::vector<std::string> readAllLines();

private:
    std::fstream m_file;
};

}
}

#endif
