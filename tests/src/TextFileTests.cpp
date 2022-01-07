/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "TextFileTests.h"
#include <Ishiko/FileSystem/ErrorCategory.hpp>
#include <Ishiko/FileSystem/TextFile.hpp>

using namespace Ishiko;
using namespace Ishiko::FileSystem;
using namespace Ishiko::Tests;

TextFileTests::TextFileTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "TextFile tests", environment)
{
    append<HeapAllocationErrorsTest>("constructor test 1", ConstructorTest1);
    append<FileComparisonTest>("create test 1", CreateTest1);
    append<HeapAllocationErrorsTest>("create test 2", CreateTest2);
    append<HeapAllocationErrorsTest>("open test 1", OpenTest1);
    append<HeapAllocationErrorsTest>("open test 2", OpenTest2);
    append<HeapAllocationErrorsTest>("readLine test 1", ReadLineTest1);
    append<HeapAllocationErrorsTest>("readLine test 2", ReadLineTest2);
    append<HeapAllocationErrorsTest>("readLine test 3", ReadLineTest3);
    append<HeapAllocationErrorsTest>("readAllLines test 1", ReadAllLinesTest1);
    append<HeapAllocationErrorsTest>("readAllLines test 2", ReadAllLinesTest2);
    append<HeapAllocationErrorsTest>("readAllLines test 3", ReadAllLinesTest3);
    append<HeapAllocationErrorsTest>("readAllLines test 4", ReadAllLinesTest4);
    append<FileComparisonTest>("write test 1", WriteTest1);
    append<FileComparisonTest>("writeLine test 1", WriteLineTest1);
}

void TextFileTests::ConstructorTest1(Test& test)
{
    TextFile file;

    ISHIKO_PASS();
}

void TextFileTests::CreateTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputPath("TextFileTests_CreateTest1.txt"));

    TextFile file;

    Error error;
    file.create(outputPath.string(), error);

    ISHIKO_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataPath("TextFileTests_CreateTest1.txt"));

    ISHIKO_PASS();
}

void TextFileTests::CreateTest2(Test& test)
{
    boost::filesystem::path outputPath(test.environment().getTestDataPath("file1.txt"));

    TextFile file;

    Error error;
    file.create(outputPath.string(), error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(error.condition().value(), FileSystem::ErrorCategory::eAlreadyExists);
    ISHIKO_PASS();
}

void TextFileTests::OpenTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_PASS();
}

void TextFileTests::OpenTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_PASS();
}

void TextFileTests::ReadLineTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    // Ignore the open error on purpose to cause an error when we try to read a line
    error.succeed();

    std::string line = file.readLine(error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_ABORT_IF_NEQ(error.condition().value(), FileSystem::ErrorCategory::eReadError);
    ISHIKO_FAIL_IF_NEQ(line, "");
    ISHIKO_PASS();
}

void TextFileTests::ReadLineTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("empty.txt"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    ISHIKO_ABORT_IF(error);

    std::string line = file.readLine(error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_ABORT_IF_NEQ(error.condition().value(), FileSystem::ErrorCategory::eEndOfFile);
    ISHIKO_FAIL_IF_NEQ(line, "");
    ISHIKO_PASS();
}

void TextFileTests::ReadLineTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    ISHIKO_ABORT_IF(error);

    std::string line1 = file.readLine(error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(line1, "hello");

    std::string line2 = file.readLine(error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_ABORT_IF_NEQ(error.condition().value(), FileSystem::ErrorCategory::eEndOfFile);
    ISHIKO_FAIL_IF_NEQ(line2, "");
    ISHIKO_PASS();
}

void TextFileTests::ReadAllLinesTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    // Ignore the open error on purpose to cause an error when we try to read a line
    error.succeed();

    std::vector<std::string> lines = file.readAllLines(error);

    ISHIKO_FAIL_IF_NOT(error);
    ISHIKO_FAIL_IF_NEQ(lines.size(), 0);
    ISHIKO_PASS();
}

void TextFileTests::ReadAllLinesTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("empty.txt"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    ISHIKO_ABORT_IF(error);

    std::vector<std::string> lines = file.readAllLines(error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_FAIL_IF_NEQ(lines.size(), 0);
    ISHIKO_PASS();
}

void TextFileTests::ReadAllLinesTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    ISHIKO_ABORT_IF(error);

    std::vector<std::string> lines = file.readAllLines(error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_ABORT_IF_NEQ(lines.size(), 1);
    ISHIKO_FAIL_IF_NEQ(lines[0], "hello");
    ISHIKO_PASS();
}

void TextFileTests::ReadAllLinesTest4(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file2.txt"));

    TextFile file;

    Error error;
    file.open(inputPath.string(), error);

    ISHIKO_ABORT_IF(error);

    std::vector<std::string> lines = file.readAllLines(error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_ABORT_IF_NEQ(lines.size(), 2);
    ISHIKO_FAIL_IF_NEQ(lines[0], "hello");
    ISHIKO_FAIL_IF_NEQ(lines[1], "world");
    ISHIKO_PASS();
}

void TextFileTests::WriteTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputPath("TextFileTests_WriteTest1.txt"));

    TextFile file;

    Error error;
    file.create(outputPath.string(), error);

    ISHIKO_FAIL_IF(error);

    file.write("hello");

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataPath("TextFileTests_WriteTest1.txt"));

    ISHIKO_PASS();
}

void TextFileTests::WriteLineTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputPath("TextFileTests_WriteLineTest1.txt"));

    TextFile file;

    Error error;
    file.create(outputPath.string(), error);

    ISHIKO_FAIL_IF(error);

    file.writeLine("hello");

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.environment().getReferenceDataPath("TextFileTests_WriteLineTest1.txt"));

    ISHIKO_PASS();
}
