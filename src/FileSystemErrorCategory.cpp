/*
    Copyright (c) 2020-2022 Xavier Leclercq
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

std::ostream& FileSystemErrorCategory::streamOut(int value, std::ostream& os) const
{
    switch (static_cast<Value>(value))
    {
    case Value::generic_error:
        os << "generic error";
        break;

    case Value::buffer_overflow:
        os << "buffer overflow";
        break;

    case Value::not_found:
        os << "not found";
        break;

    case Value::already_exists:
        os << "already exists";
        break;

    case Value::end_of_file:
        os << "end of file";
        break;

    case Value::read_error:
        os << "read error";
        break;

    default:
        os << "unknown value";
        break;
    }
    return os;
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
