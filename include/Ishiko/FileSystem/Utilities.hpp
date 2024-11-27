// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_UTILITIES_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_UTILITIES_HPP

#include <boost/filesystem.hpp>
#include <Ishiko/BasePlatform.hpp>
#include <Ishiko/Errors.hpp>
#include <cstddef>
#include <string>
#include <vector>

namespace Ishiko
{
    namespace FileSystem
    {
        class CopyOption
        {
        public:
            enum Value
            {
                none = boost::filesystem::copy_options::none,
                create_directories = (1u << 3),
                recursive = boost::filesystem::copy_options::recursive
            };
        };

        bool Exists(const char* path);
        bool Exists(const std::string& path);
        bool Exists(const boost::filesystem::path& path);
        size_t GetFileSize(const char* path);
        size_t GetFileSize(const char* path, Error& error) noexcept;
        bool IsDirectory(const char* path, Error& error) noexcept;
        bool IsEmpty(const char* path, Error& error) noexcept;
        void ToAbsolutePath(const char* path, std::string& absolutePath);
        void ToAbsolutePath(const std::string& path, std::string& absolutePath);
        void CreateEmptyFile(const std::string& path, Error& error) noexcept;
        void CreateEmptyFile(const boost::filesystem::path& path, Error& error) noexcept;

        void Copy(const boost::filesystem::path& source_path, const boost::filesystem::path& target_path,
            unsigned int options = CopyOption::none);
        // This function should simply be called CopyFile. Unfortunately the Windows system header define a macro named
        // CopyFile that interferes. Since it is a macro namespacing doesn't solve the issue. The issue it creates is
        // also obscure to diagnose so it was simpler to avoid the clash entirely.
        void CopySingleFile(const boost::filesystem::path& source_path, const boost::filesystem::path& target_path);
        void CopySingleFile(const boost::filesystem::path& sourcePath, const boost::filesystem::path& targetPath,
            Error& error) noexcept;
        void CopySingleFile(const boost::filesystem::path& source_path, const boost::filesystem::path& target_path,
            unsigned int options);
        void CopySingleFile(const boost::filesystem::path& source_path, const boost::filesystem::path& target_path,
            unsigned int options, Error& error) noexcept;
        size_t ReadFile(const char* filename, char* buffer, size_t bufferSize, Error& error) noexcept;
        std::string ReadFile(const char* filename);
        std::string ReadFile(const char* filename, Error& error) noexcept;
        std::string ReadFile(const boost::filesystem::path& path);
        std::string ReadFile(const boost::filesystem::path& path, Error& error) noexcept;
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
        void GetVolumeList(std::vector<std::string>& volumeNames, Error& error) noexcept;
#endif
    }
}

#endif
