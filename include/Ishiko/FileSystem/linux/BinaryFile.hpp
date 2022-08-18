/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_LINUX_BINARYFILE_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_LINUX_BINARYFILE_HPP

#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class BinaryFile
{
public:
    BinaryFile() = default;
    BinaryFile(const BinaryFile& other) = delete;
    BinaryFile(BinaryFile&& other);
    ~BinaryFile();

    BinaryFile& operator=(const BinaryFile& other) = delete;
    BinaryFile& operator=(BinaryFile&& other);

    static BinaryFile Create(const boost::filesystem::path& path, Error& error);
    static BinaryFile Create(const std::string& path, Error& error);
    void close();

    void write(const char* buffer, size_t length, Error& error);
    void flush();

private:
    int m_file_descriptor{-1};
};

}

#endif
