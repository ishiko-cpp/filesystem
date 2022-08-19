/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_FILESYSTEMERRORCATEGORY_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_FILESYSTEMERRORCATEGORY_HPP

#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class FileSystemErrorCategory : public ErrorCategory
{
public:
    enum class Value
    {
        generic_error = -1,
        buffer_overflow = -2,
        not_found = -3,
        already_exists = -4,
        end_of_file = -5,
        read_error = -6
    };

    static const FileSystemErrorCategory& Get() noexcept;

    const char* name() const noexcept override;
    std::ostream& streamOut(int value, std::ostream& os) const override;

private:
    FileSystemErrorCategory() noexcept = default;
};

void Throw(FileSystemErrorCategory::Value value, const char* file, int line);
void Fail(FileSystemErrorCategory::Value value, Error& error) noexcept;
void Fail(FileSystemErrorCategory::Value value, const std::string& message, const char* file, int line,
    Error& error) noexcept;
void Fail(FileSystemErrorCategory::Value value, const std::wstring& message, const char* file, int line,
    Error& error) noexcept;
bool operator==(const ErrorCondition& error, FileSystemErrorCategory::Value value);
bool operator!=(const ErrorCondition& error, FileSystemErrorCategory::Value value);

}

#endif
