/*
    Copyright (c) 2022-2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_BINARYFILE_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_BINARYFILE_HPP

#include <Ishiko/BasePlatform.hpp>

#if ISHIKO_OS == ISHIKO_OS_LINUX
#include "linux/BinaryFile.hpp"
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
#include "windows/BinaryFile.hpp"
#else
#error Unsupported or unrecognized OS
#endif

#endif
