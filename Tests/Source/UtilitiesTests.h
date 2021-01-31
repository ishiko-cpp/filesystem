/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_FILESYSTEM_TESTS_UTILITIES_TESTS_H_
#define _ISHIKO_FILESYSTEM_TESTS_UTILITIES_TESTS_H_

#include <Ishiko/Platform/OS.h>
#include <Ishiko/TestFramework/TestFrameworkCore.h>

class UtilitiesTests : public Ishiko::Tests::TestSequence
{
public:
    UtilitiesTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ExistsTest1(Ishiko::Tests::Test& test);
    static void ExistsTest2(Ishiko::Tests::Test& test);
    static void ExistsTest3(Ishiko::Tests::Test& test);
    static void IsDirectoryTest1(Ishiko::Tests::Test& test);
    static void IsDirectoryTest2(Ishiko::Tests::Test& test);
    static void IsDirectoryTest3(Ishiko::Tests::Test& test);
    static void IsEmptyTest1(Ishiko::Tests::Test& test);
    static void IsEmptyTest2(Ishiko::Tests::Test& test);
    static void IsEmptyTest3(Ishiko::Tests::Test& test);
    static void IsEmptyTest4(Ishiko::Tests::Test& test);
    static void IsEmptyTest5(Ishiko::Tests::Test& test);
    static void ToAbsolutePathTest1(Ishiko::Tests::Test& test);
    static void ToAbsolutePathTest2(Ishiko::Tests::Test& test);
    static void ReadFileTest1(Ishiko::Tests::Test& test);
    static void ReadFileTest2(Ishiko::Tests::Test& test);
    static void ReadFileTest3(Ishiko::Tests::Test& test);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    static void GetVolumeListTest1(Ishiko::Tests::Test& test);
#endif
};

#endif
