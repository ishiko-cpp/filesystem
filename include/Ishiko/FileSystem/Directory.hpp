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
namespace FileSystem
{

class Directory
{
public:
    Directory(const char* path);

    template<typename Callable> void forEachRegularFile(Callable&& callback, bool recursive);

private:
    std::string m_path;
};

template<typename Callable>
void Directory::forEachRegularFile(Callable&& callback, bool recursive)
{
    if (recursive)
    {
        boost::filesystem::recursive_directory_iterator iterator(m_path);
        boost::filesystem::recursive_directory_iterator iterator_end;
        while (iterator != iterator_end)
        {
            if (boost::filesystem::is_regular_file(iterator->status()))
            {
                callback(iterator->path().generic_string());
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
                callback(iterator->path().generic_string());
            }
            ++iterator;
        }
    }
}

}
}

#endif
