/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_FILESYSTEMERRORCATEGORY_HPP_
#define _ISHIKO_CPP_FILESYSTEM_FILESYSTEMERRORCATEGORY_HPP_

#include <Ishiko/Errors.hpp>

namespace Ishiko
{

class FileSystemErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum class Value
    {
        generic = -1,
        bufferOverflow = -2,
        notFound = -3,
        alreadyExists = -4,
        endOfFile = -5,
        readError = -6
    };

    static const FileSystemErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    FileSystemErrorCategory() noexcept = default;
};

void Fail(Error& error, FileSystemErrorCategory::Value value) noexcept;
void Fail(Error& error, FileSystemErrorCategory::Value value, const std::string& message, const char* file,
    int line) noexcept;
bool operator==(const ErrorCondition& error, FileSystemErrorCategory::Value value);
bool operator!=(const ErrorCondition& error, FileSystemErrorCategory::Value value);

}

#endif
