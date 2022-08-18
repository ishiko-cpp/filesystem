/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "BinaryFileTests.hpp"
#include "Ishiko/FileSystem/BinaryFile.hpp"
#include "Ishiko/FileSystem/FileSystemErrorCategory.hpp"

using namespace Ishiko;

BinaryFileTests::BinaryFileTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BinaryFile tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("Create test 2", CreateTest2);
    append<HeapAllocationErrorsTest>("write test 1", WriteTest1);
    append<HeapAllocationErrorsTest>("resize test 1", ResizeTest1);
}

void BinaryFileTests::ConstructorTest1(Test& test)
{
    BinaryFile file;

    ISHIKO_TEST_PASS();
}

void BinaryFileTests::CreateTest1(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_CreateTest1.bin"));

    Error error;
    BinaryFile file = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_CreateTest1.bin");
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::CreateTest2(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_CreateTest2.bin"));

    Error error;
    BinaryFile file1 = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file1.close();

    BinaryFile file2 = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.condition(), FileSystemErrorCategory::Value::already_exists);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_CreateTest2.bin");
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::WriteTest1(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_WriteTest1.bin"));

    Error error;
    BinaryFile file = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.write("hello\r\n", 7, error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_WriteTest1.bin");
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::ResizeTest1(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_ResizeTest1.bin"));

    Error error;
    BinaryFile file = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.resize(5);
    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_ResizeTest1.bin");
    ISHIKO_TEST_PASS();
}
