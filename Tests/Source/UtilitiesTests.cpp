/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "UtilitiesTests.h"
#include "Ishiko/FileSystem/Utilities.h"

using namespace Ishiko::Tests;

UtilitiesTests::UtilitiesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Utilities tests", environment)
{
    append<HeapAllocationErrorsTest>("ReadFile test 1", ReadFileTest1);
    append<HeapAllocationErrorsTest>("ReadFile test 2", ReadFileTest2);
    append<HeapAllocationErrorsTest>("ReadFile test 3", ReadFileTest3);
}

void UtilitiesTests::ReadFileTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");

    Ishiko::Error error(0);
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(bytesRead, 5);
    ISHTF_PASS();
}

void UtilitiesTests::ReadFileTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "doesnotexist");

    Ishiko::Error error(0);
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(bytesRead, 0);
    ISHTF_PASS();
}

void UtilitiesTests::ReadFileTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");

    Ishiko::Error error(0);
    const int bufferSize = 2;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.code(), -2);
    ISHTF_FAIL_IF_NEQ(bytesRead, 5);
    ISHTF_PASS();
}
