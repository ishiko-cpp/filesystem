/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "Directory.h"
#include <boost/filesystem.hpp>

namespace Ishiko
{
namespace FileSystem
{

Directory::Directory(const char* path)
    : m_path(path)
{
}

void Directory::forEachRegularFile(std::function<void(const std::string& path)> callback, bool recursive)
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
