/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_TESTS_BINARYFILETESTS_HPP_
#define _ISHIKO_CPP_FILESYSTEM_TESTS_BINARYFILETESTS_HPP_

#include <Ishiko/TestFramework/Core.hpp>

class BinaryFileTests : public Ishiko::TestSequence
{
public:
    BinaryFileTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void ConstructorTest1(Ishiko::Test& test);
    static void CreateTest1(Ishiko::Test& test);
    static void CreateTest2(Ishiko::Test& test);
    static void OpenTest1(Ishiko::Test& test);
    static void OpenTest2(Ishiko::Test& test);
    static void ReadTest1(Ishiko::Test& test);
    static void WriteTest1(Ishiko::Test& test);
    static void ResizeTest1(Ishiko::Test& test);
};

#endif
