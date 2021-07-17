/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_FILESYSTEM_ERRORCATEGORY_H_
#define _ISHIKO_FILESYSTEM_ERRORCATEGORY_H_

#include <Ishiko/Errors.h>

namespace Ishiko
{
namespace FileSystem
{

class ErrorCategory : public Ishiko::ErrorCategory
{
public:
    enum EErrorValues
    {
        eGeneric = -1,
        eBufferOverflow = -2,
        eNotFound = -3,
        eAlreadyExists = -4,
        eEndOfFile = -5,
        eReadError = -6
    };

    static const ErrorCategory& Get() noexcept;

    const char* name() const noexcept override;

private:
    ErrorCategory() noexcept = default;
};

void Fail(Error& error, ErrorCategory::EErrorValues value) noexcept;
void Fail(Error& error, ErrorCategory::EErrorValues value, const std::string& message, const char* file,
    int line) noexcept;

}
}

#endif
