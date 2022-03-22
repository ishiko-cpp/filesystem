/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_TESTS_DIRECTORYTESTS_H_
#define _ISHIKO_CPP_FILESYSTEM_TESTS_DIRECTORYTESTS_H_

#include <Ishiko/Tests/Core.hpp>

class DirectoryTests : public Ishiko::TestSequence
{
public:
    DirectoryTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void ForEachRegularFileTest1(Ishiko::Test& test);
    static void ForEachRegularFileTest2(Ishiko::Test& test);
    static void ForEachRegularFileTest3(Ishiko::Test& test);
    static void ForEachRegularFileTest4(Ishiko::Test& test);
    static void ForEachRegularFileTest5(Ishiko::Test& test);
    static void ForEachRegularFileTest6(Ishiko::Test& test);
    static void ForEachRegularFileTest7(Ishiko::Test& test);
    static void ForEachRegularFileTest8(Ishiko::Test& test);
};

#endif
