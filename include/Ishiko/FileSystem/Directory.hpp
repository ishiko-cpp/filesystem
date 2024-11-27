// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_DIRECTORY_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_DIRECTORY_HPP

#include <boost/filesystem.hpp>
#include <functional>
#include <string>

namespace Ishiko
{

class Directory
{
public:
    Directory(const char* path);
    Directory(boost::filesystem::path path);

    template<typename Callable> void forEachRegularFile(Callable&& callback, bool recursive) const;

    size_t getRegularFilesCount(bool recursive) const;

private:
    boost::filesystem::path m_path;
};

template<typename Callable>
void Directory::forEachRegularFile(Callable&& callback, bool recursive) const
{
    if (recursive)
    {
        boost::filesystem::recursive_directory_iterator iterator(m_path);
        boost::filesystem::recursive_directory_iterator iterator_end;
        while (iterator != iterator_end)
        {
            if (boost::filesystem::is_regular_file(iterator->status()))
            {
                callback(iterator->path());
            }
            ++iterator;
        }
    }
    else
    {
        boost::filesystem::directory_iterator iterator(m_path);
        boost::filesystem::directory_iterator iterator_end;
        while (iterator != iterator_end)
        {
            if (boost::filesystem::is_regular_file(iterator->status()))
            {
                callback(iterator->path());
            }
            ++iterator;
        }
    }
}

}

#endif
