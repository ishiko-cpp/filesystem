/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "TextFile.h"
#include "ErrorCategory.h"

namespace Ishiko
{
namespace FileSystem
{

void TextFile::open(const std::string& path, Error& error)
{
    m_file.open(path);
    FailIfOpenFileError(error, m_file, path, __FILE__, __LINE__);
}

std::string TextFile::readLine(Error& error)
{
    std::string result;
    
    std::getline(m_file, result);
    if (m_file.fail() && m_file.eof())
    {
        Fail(error, ErrorCategory::eEndOfFile);
    }

    // TODO: handle other errors

    return result;
}

std::vector<std::string> TextFile::readAllLines()
{
    std::vector<std::string> result;

    while (true)
    {
        Error error;
        std::string line = readLine(error);
        if (error)
        {
            // TODO: handle errors other than EOF
            break;
        }
        result.push_back(line);
    }

    return result;
}

}
}
