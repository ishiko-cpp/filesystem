// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_TESTS_UTILITIESTESTS_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_TESTS_UTILITIESTESTS_HPP

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
    static void CopyTest1(Ishiko::Test& test);
    static void CopyTest2(Ishiko::Test& test);
    static void CopySingleFileTest1(Ishiko::Test& test);
    static void CopySingleFileTest2(Ishiko::Test& test);
    static void CopySingleFileTest3(Ishiko::Test& test);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    static void GetVolumeListTest1(Ishiko::Test& test);
#endif
};

#endif
