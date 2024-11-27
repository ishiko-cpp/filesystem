// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_FILESYSTEM_TESTS_BINARYFILETESTS_HPP
#define GUARD_ISHIKO_CPP_FILESYSTEM_TESTS_BINARYFILETESTS_HPP

#include <Ishiko/TestFramework/Core.hpp>

class BinaryFileTests : public Ishiko::TestSequence
{
public:
    BinaryFileTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::Test& test);
    static void CreateTest2(Ishiko::Test& test);
    static void StaticCreateTest1(Ishiko::Test& test);
    static void StaticCreateTest2(Ishiko::Test& test);
    static void OpenTest1(Ishiko::Test& test);
    static void OpenTest2(Ishiko::Test& test);
    static void StaticOpenTest1(Ishiko::Test& test);
    static void StaticOpenTest2(Ishiko::Test& test);
    static void ReadTest1(Ishiko::Test& test);
    static void ReadTest2(Ishiko::Test& test);
    static void WriteTest1(Ishiko::Test& test);
    static void WriteTest2(Ishiko::Test& test);
    static void ResizeTest1(Ishiko::Test& test);
    static void ResizeTest2(Ishiko::Test& test);
};

#endif
