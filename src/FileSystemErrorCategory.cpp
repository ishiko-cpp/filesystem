/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "FileSystemErrorCategory.hpp"

namespace Ishiko
{

const FileSystemErrorCategory& FileSystemErrorCategory::Get() noexcept
{
    static FileSystemErrorCategory theCategory;
    return theCategory;
}

const char* FileSystemErrorCategory::name() const noexcept
{
    return "Ishiko::FileSystemErrorCategory";
}

void Throw(FileSystemErrorCategory::Value value, const char* file, int line)
{
    throw Exception(static_cast<int>(value), FileSystemErrorCategory::Get(), file, line);
}

void Fail(Error& error, FileSystemErrorCategory::Value value) noexcept
{
    error.fail(static_cast<int>(value), FileSystemErrorCategory::Get());
}

void Fail(Error& error, FileSystemErrorCategory::Value value, const std::string& message, const char* file,
    int line) noexcept
{
    error.fail(static_cast<int>(value), FileSystemErrorCategory::Get(), message, file, line);
}

bool operator==(const ErrorCondition& error, FileSystemErrorCategory::Value value)
{
    return ((&error.category() == &FileSystemErrorCategory::Get()) && (error.value() == static_cast<int>(value)));
}

bool operator!=(const ErrorCondition& error, FileSystemErrorCategory::Value value)
{
    return !(error == value);
}

}
