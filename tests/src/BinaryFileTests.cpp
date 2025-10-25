// SPDX-FileCopyrightText: 2000-2025 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "BinaryFileTests.hpp"
#include "Ishiko/FileSystem/BinaryFile.hpp"
#include "Ishiko/FileSystem/FileSystemErrorCategory.hpp"

using namespace Ishiko;

BinaryFileTests::BinaryFileTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BinaryFile tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("create test 2", CreateTest2);
    append<HeapAllocationErrorsTest>("Create test 1", StaticCreateTest1);
    append<HeapAllocationErrorsTest>("Create test 2", StaticCreateTest2);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("Open test 1", StaticOpenTest1);
    append<HeapAllocationErrorsTest>("Open test 2", StaticOpenTest2);
    append<HeapAllocationErrorsTest>("read test 1", ReadTest1);
    append<HeapAllocationErrorsTest>("read test 2", ReadTest2);
    append<HeapAllocationErrorsTest>("write test 1", WriteTest1);
    append<HeapAllocationErrorsTest>("write test 2", WriteTest2);
    append<HeapAllocationErrorsTest>("resize test 1", ResizeTest1);
    append<HeapAllocationErrorsTest>("resize test 2", ResizeTest2);
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
    BinaryFile file;
    file.create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_CreateTest1.bin");
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::CreateTest2(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_CreateTest2.bin"));

    Error error;
    BinaryFile file1;
    file1.create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file1.close();

    BinaryFile file2;
    file2.create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::already_exists);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_CreateTest2.bin");
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::StaticCreateTest1(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_StaticCreateTest1.bin"));

    Error error;
    BinaryFile file = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_StaticCreateTest1.bin",
        "BinaryFileTests_CreateTest1.bin");
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::StaticCreateTest2(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_StaticCreateTest2.bin"));

    Error error;
    BinaryFile file1 = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file1.close();

    BinaryFile file2 = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::already_exists);
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_StaticCreateTest2.bin",
        "BinaryFileTests_CreateTest2.bin");
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::OpenTest1(Test& test)
{
    Error error;
    BinaryFile file;
    file.open(test.context().getDataPath("BinaryFileTests_OpenTest1.bin"), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(file.size(), 0);
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::OpenTest2(Test& test)
{
    Error error;
    BinaryFile file;
    file.open(test.context().getDataPath("does_not_exist"), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::not_found);
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::StaticOpenTest1(Test& test)
{
    Error error;
    BinaryFile file = BinaryFile::Open(test.context().getDataPath("BinaryFileTests_OpenTest1.bin"), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(file.size(), 0);
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::StaticOpenTest2(Test& test)
{
    Error error;
    BinaryFile file = BinaryFile::Open(test.context().getDataPath("does_not_exist"), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::not_found);
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::ReadTest1(Test& test)
{
    Error error;
    BinaryFile file = BinaryFile::Open(test.context().getDataPath("BinaryFileTests_ReadTest1.bin"), error);

    ISHIKO_TEST_FAIL_IF(error);

    char buffer[6];
    size_t read_count = file.read(6, buffer, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(read_count, 4);
    ISHIKO_TEST_FAIL_IF_NEQ(std::string(buffer, 4), "data");

    read_count = file.read(6, buffer, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(read_count, 0);
    ISHIKO_TEST_PASS();
}

void BinaryFileTests::ReadTest2(Test& test)
{
    Error error;
    BinaryFile file = BinaryFile::Open(test.context().getDataPath("BinaryFileTests_ReadTest1.bin"), error);

    ISHIKO_TEST_FAIL_IF(error);

    char buffer[6];
    size_t read_count = file.read(1, 6, buffer, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(read_count, 3);
    ISHIKO_TEST_FAIL_IF_NEQ(std::string(buffer, 3), "ata");

    read_count = file.read(4, 6, buffer, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(read_count, 0);
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

void BinaryFileTests::WriteTest2(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_WriteTest2.bin"));

    Error error;
    BinaryFile file = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_TEST_FAIL_IF(error);

    file.write(2, "hello\r\n", 7, error);

    ISHIKO_TEST_FAIL_IF(error);

    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_WriteTest2.bin");
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

void BinaryFileTests::ResizeTest2(Test& test)
{
    boost::filesystem::path outputPath(test.context().getOutputPath("BinaryFileTests_ResizeTest2.bin"));

    Error error;
    BinaryFile file = BinaryFile::Create(outputPath, error);

    ISHIKO_TEST_FAIL_IF(error);

    file.resize(5);
    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_ResizeTest2.bin", "BinaryFileTests_ResizeTest1.bin");

    file.open(outputPath, error);

    ISHIKO_TEST_FAIL_IF(error);

    file.resize(8);
    file.close();

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("BinaryFileTests_ResizeTest2.bin");
    ISHIKO_TEST_PASS();
}
