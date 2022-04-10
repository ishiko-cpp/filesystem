/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_TESTS_TEXTFILETESTS_H_
#define _ISHIKO_CPP_FILESYSTEM_TESTS_TEXTFILETESTS_H_

#include <Ishiko/TestFramework/Core.hpp>

class TextFileTests : public Ishiko::TestSequence
{
public:
    TextFileTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::FileComparisonTest& test);
    static void CreateTest2(Ishiko::Test& test);
    static void OpenTest1(Ishiko::Test& test);
    static void OpenTest2(Ishiko::Test& test);
    static void ReadLineTest1(Ishiko::Test& test);
    static void ReadLineTest2(Ishiko::Test& test);
    static void ReadLineTest3(Ishiko::Test& test);
    static void ReadAllLinesTest1(Ishiko::Test& test);
    static void ReadAllLinesTest2(Ishiko::Test& test);
    static void ReadAllLinesTest3(Ishiko::Test& test);
    static void ReadAllLinesTest4(Ishiko::Test& test);
    static void ForEachLineTest1(Ishiko::Test& test);
    static void ForEachLineTest2(Ishiko::Test& test);
    static void ForEachLineTest3(Ishiko::Test& test);
    static void ForEachLineTest4(Ishiko::Test& test);
    static void WriteTest1(Ishiko::FileComparisonTest& test);
    static void WriteLineTest1(Ishiko::FileComparisonTest& test);
};

#endif
