/*
    Copyright (c) 2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "BinaryFileTests.hpp"
#include "Ishiko/FileSystem/BinaryFile.hpp"

using namespace boost::filesystem;
using namespace Ishiko;
using namespace Ishiko::Tests;

BinaryFileTests::BinaryFileTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BinaryFile tests", context)
{
    append<FileComparisonTest>("Create test 1", CreateTest1);
    append<FileComparisonTest>("write test 1", WriteTest1);
}

void BinaryFileTests::CreateTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputPath("BinaryFileTests_CreateTest1.bin"));

    Error error;
    BinaryFile file = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_FAIL_IF(error);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataPath("BinaryFileTests_CreateTest1.bin"));

    ISHIKO_PASS();
}

void BinaryFileTests::WriteTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputPath("BinaryFileTests_WriteTest1.bin"));

    Error error;
    BinaryFile file = BinaryFile::Create(outputPath.string(), error);

    ISHIKO_FAIL_IF(error);

    file.write("hello\r\n", 7);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(test.context().getReferenceDataPath("BinaryFileTests_WriteTest1.bin"));

    ISHIKO_PASS();
}
