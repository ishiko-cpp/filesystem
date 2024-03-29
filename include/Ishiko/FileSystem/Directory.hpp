/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_DIRECTORY_HPP_
#define _ISHIKO_CPP_FILESYSTEM_DIRECTORY_HPP_

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
