/*
    Copyright (c) 2020-2023 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_TESTS_UTILITIESTESTS_H_
#define _ISHIKO_CPP_FILESYSTEM_TESTS_UTILITIESTESTS_H_

#include <Ishiko/BasePlatform.hpp>
#include <Ishiko/TestFramework/Core.hpp>

class UtilitiesTests : public Ishiko::TestSequence
{
public:
    UtilitiesTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ExistsTest1(Ishiko::Test& test);
    static void ExistsTest2(Ishiko::Test& test);
    static void ExistsTest3(Ishiko::Test& test);
    static void GetFileSizeTest1(Ishiko::Test& test);
    static void GetFileSizeTest2(Ishiko::Test& test);
    static void GetFileSizeTest3(Ishiko::Test& test);
    static void GetFileSizeTest4(Ishiko::Test& test);
    static void IsDirectoryTest1(Ishiko::Test& test);
    static void IsDirectoryTest2(Ishiko::Test& test);
    static void IsDirectoryTest3(Ishiko::Test& test);
    static void IsEmptyTest1(Ishiko::Test& test);
    static void IsEmptyTest2(Ishiko::Test& test);
    static void IsEmptyTest3(Ishiko::Test& test);
    static void IsEmptyTest4(Ishiko::Test& test);
    static void IsEmptyTest5(Ishiko::Test& test);
    static void ToAbsolutePathTest1(Ishiko::Test& test);
    static void ToAbsolutePathTest2(Ishiko::Test& test);
    static void CreateEmptyFileTest1(Ishiko::Test& test);
    static void CreateEmptyFileTest2(Ishiko::Test& test);
    static void ReadFileTest1(Ishiko::Test& test);
    static void ReadFileTest2(Ishiko::Test& test);
    static void ReadFileTest3(Ishiko::Test& test);
    static void ReadFileTest4(Ishiko::Test& test);
    static void ReadFileTest5(Ishiko::Test& test);
    static void ReadFileTest6(Ishiko::Test& test);
    static void ReadFileTest7(Ishiko::Test& test);
    static void ReadFileTest8(Ishiko::Test& test);
    static void ReadFileTest9(Ishiko::Test& test);
    static void ReadFileTest10(Ishiko::Test& test);
    static void ReadFileTest11(Ishiko::Test& test);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    static void GetVolumeListTest1(Ishiko::Test& test);
#endif
};

#endif
