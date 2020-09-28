/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#ifndef _ISHIKO_FILESYSTEM_TESTS_UTILITIES_TESTS_H_
#define _ISHIKO_FILESYSTEM_TESTS_UTILITIES_TESTS_H_

#include "Ishiko/TestFramework/TestFrameworkCore.h"

class UtilitiesTests : public Ishiko::Tests::TestSequence
{
public:
    UtilitiesTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestEnvironment& environment);

private:
    static void ReadFileTest1(Ishiko::Tests::Test& test);
};

#endif
