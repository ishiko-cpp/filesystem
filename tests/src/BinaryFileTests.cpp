/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "BinaryFileTests.hpp"
#include "Ishiko/FileSystem/BinaryFile.hpp"

using namespace Ishiko;
using namespace Ishiko::Tests;

BinaryFileTests::BinaryFileTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BinaryFile tests", context)
{
    append<HeapAllocationErrorsTest>("constructor test 1", ConstructorTest1);
}

void BinaryFileTests::ConstructorTest1(Test& test)
{
    BinaryFile file;

    ISHIKO_PASS();
}
