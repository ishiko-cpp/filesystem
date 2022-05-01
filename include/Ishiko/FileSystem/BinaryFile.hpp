/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_BINARYFILE_HPP_
#define _ISHIKO_CPP_FILESYSTEM_BINARYFILE_HPP_

#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>
#include <fstream>

namespace Ishiko
{

class BinaryFile
{
public:
    BinaryFile() = default;
    static BinaryFile Create(const boost::filesystem::path& path, Error& error);
    static BinaryFile Create(const std::string& path, Error& error);
    void close();

    void write(const char* buffer, size_t length);
    void flush();

private:
    std::fstream m_file;
};

}

#endif
