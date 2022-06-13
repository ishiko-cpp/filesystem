/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "Directory.hpp"

namespace Ishiko
{

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

}
