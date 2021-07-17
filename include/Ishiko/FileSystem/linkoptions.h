/*
    Copyright (c) 2017-2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_FILESYSTEM_LINKOPTIONS_H_
#define _ISHIKO_FILESYSTEM_LINKOPTIONS_H_

#ifdef _DEBUG
#pragma comment(lib, "IshikoFileSystem-d.lib")
#else
#pragma comment(lib, "IshikoFileSystem.lib")
#endif

#endif
