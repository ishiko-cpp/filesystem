/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_TESTS_DIRECTORYTESTS_H_
#define _ISHIKO_CPP_FILESYSTEM_TESTS_DIRECTORYTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class DirectoryTests : public Ishiko::Tests::TestSequence
{
public:
    DirectoryTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest1(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest2(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest3(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest4(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest5(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest6(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest7(Ishiko::Tests::Test& test);
    static void ForEachRegularFileTest8(Ishiko::Tests::Test& test);
};

#endif
