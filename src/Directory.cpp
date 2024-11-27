// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "Directory.hpp"

using namespace Ishiko;

Directory::Directory(const char* path)
    : m_path(path)
{
}

Directory::Directory(boost::filesystem::path path)
    : m_path(std::move(path))
{
}

size_t Directory::getRegularFilesCount(bool recursive) const
{
    size_t result = 0;

    forEachRegularFile(
        [&result](const boost::filesystem::path& filepath)
        {
            ++result;
        },
        recursive);

    return result;
}
