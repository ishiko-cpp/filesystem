/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#ifndef _ISHIKO_CPP_FILESYSTEM_TESTS_BINARYFILETESTS_HPP_
#define _ISHIKO_CPP_FILESYSTEM_TESTS_BINARYFILETESTS_HPP_

#include <Ishiko/Tests/Core.hpp>

class BinaryFileTests : public Ishiko::Tests::TestSequence
{
public:
    BinaryFileTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void CreateTest1(Ishiko::Tests::FileComparisonTest& test);
    static void WriteTest1(Ishiko::Tests::FileComparisonTest& test);
};

#endif
