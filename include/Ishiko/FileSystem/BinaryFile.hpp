// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

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
