// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_TESTS_DIRECTORYTESTS_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_TESTS_DIRECTORYTESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

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
    static void GetRegularFilesCountTest1(Ishiko::Test& test);
    static void GetRegularFilesCountTest2(Ishiko::Test& test);
    static void GetRegularFilesCountTest3(Ishiko::Test& test);
};

#endif
