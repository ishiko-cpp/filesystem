/*
    Copyright (c) 2022-2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_WINDOWS_BINARYFILE_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_WINDOWS_BINARYFILE_HPP

#include <boost/filesystem.hpp>
#include <Ishiko/Errors.hpp>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>    // TODO: provide fwd declares instead

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
    static BinaryFile Open(const boost::filesystem::path& path, Error& error);
    static BinaryFile Open(const std::string& path, Error& error);

    void create(const boost::filesystem::path& path, Error& error);
    void create(const char* path, Error& error);
    void create(const wchar_t* path, Error& error);
    void open(const boost::filesystem::path& path, Error& error);
    void open(const char* path, Error& error);
    void open(const wchar_t* path, Error& error);
    void close();

    size_t size();
    void resize(size_t new_size);

    size_t getFilePointer();
    void setFilePointer(size_t pos);

    size_t read(size_t length, char* buffer, Error& error);
    size_t read(size_t pos, size_t length, char* buffer, Error& error);

    void write(const char* buffer, size_t length, Error& error);
    void write(size_t pos, const char* buffer, size_t length, Error& error);
    void flush();

private:
    HANDLE m_file_handle{INVALID_HANDLE_VALUE};
};

}

#endif
