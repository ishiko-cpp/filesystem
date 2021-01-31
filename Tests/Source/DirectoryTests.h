/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_FILESYSTEM_TESTS_DIRECTORYTESTS_H_
#define _ISHIKO_FILESYSTEM_TESTS_DIRECTORYTESTS_H_

#include <Ishiko/TestFramework/TestFrameworkCore.h>

class DirectoryTests : public Ishiko::Tests::TestSequence
{
public:
    DirectoryTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest1(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest2(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest3(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest4(Ishiko::Tests::Test& test);
};

#endif
