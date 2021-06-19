/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_FILESYSTEM_TESTS_TEXTFILETESTS_H_
#define _ISHIKO_FILESYSTEM_TESTS_TEXTFILETESTS_H_

#include <Ishiko/TestFramework/TestFrameworkCore.h>

class TextFileTests : public Ishiko::Tests::TestSequence
{
public:
    TextFileTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void CreateTest1(Ishiko::Tests::FileComparisonTest& test);
    static void CreateTest2(Ishiko::Tests::Test& test);
    static void OpenTest1(Ishiko::Tests::Test& test);
    static void OpenTest2(Ishiko::Tests::Test& test);
    static void ReadLineTest1(Ishiko::Tests::Test& test);
    static void ReadLineTest2(Ishiko::Tests::Test& test);
    static void ReadAllLinesTest1(Ishiko::Tests::Test& test);
    static void ReadAllLinesTest2(Ishiko::Tests::Test& test);
    static void ReadAllLinesTest3(Ishiko::Tests::Test& test);
    static void WriteTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteLineTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif
