/*
    Copyright (c) 2020-2024 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "FileSystemErrorCategory.hpp"

using namespace Ishiko;

const FileSystemErrorCategory& FileSystemErrorCategory::Get() noexcept
{
    static FileSystemErrorCategory theCategory;
    return theCategory;
}

const char* FileSystemErrorCategory::name() const noexcept
{
    return "Ishiko::FileSystemErrorCategory";
}

const char* FileSystemErrorCategory::message(int ev, char* buffer, size_t len) const noexcept
{
    switch (static_cast<Value>(ev))
    {
    case Value::generic_error:
        return "generic error";

    case Value::buffer_overflow:
        return "buffer overflow";

    case Value::not_found:
        return "not found";

    case Value::already_exists:
        return "already exists";

    case Value::end_of_file:
        return "end of file";

    case Value::read_error:
        return "read error";

    default:
        return "unknown value";
    }
}

void Ishiko::Throw(FileSystemErrorCategory::Value value, const char* file, int line)
{
    throw Exception(static_cast<int>(value), FileSystemErrorCategory::Get(), file, line);
}

void Ishiko::Fail(FileSystemErrorCategory::Value value, Error& error) noexcept
{
    error.fail(FileSystemErrorCategory::Get(), static_cast<int>(value));
}

void Ishiko::Fail(FileSystemErrorCategory::Value value, const std::string& message, const char* file, int line,
    Error& error) noexcept
{
    error.fail(FileSystemErrorCategory::Get(), static_cast<int>(value), message, file, line);
}

void Ishiko::Fail(FileSystemErrorCategory::Value value, const std::wstring& message, const char* file, int line,
    Error& error) noexcept
{
    error.fail(FileSystemErrorCategory::Get(), static_cast<int>(value), message, file, line);
}

bool Ishiko::operator==(const ErrorCondition& error, FileSystemErrorCategory::Value value)
{
    return ((&error.category() == &FileSystemErrorCategory::Get()) && (error.value() == static_cast<int>(value)));
}

bool Ishiko::operator!=(const ErrorCondition& error, FileSystemErrorCategory::Value value)
{
    return !(error == value);
}
