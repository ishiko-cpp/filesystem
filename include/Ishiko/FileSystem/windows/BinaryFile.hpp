// SPDX-FileCopyrightText: 2000-2025 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_WINDOWS_BINARYFILE_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_WINDOWS_BINARYFILE_HPP

#include <Ishiko/BasePlatform/windows/IshikoWindows.hpp>
#include <Ishiko/Errors.hpp>
#include <boost/filesystem.hpp>

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
