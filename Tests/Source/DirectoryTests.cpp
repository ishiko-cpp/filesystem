/*
    Copyright (c) 2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "DirectoryTests.h"
#include "Ishiko/FileSystem/Directory.h"

using namespace Ishiko::Tests;

DirectoryTests::DirectoryTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Directory tests", environment)
{
    append<HeapAllocationErrorsTest>("constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 1", ForEachRegularFileTest1);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 2", ForEachRegularFileTest2);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 3", ForEachRegularFileTest3);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 4", ForEachRegularFileTest4);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 5", ForEachRegularFileTest5);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 6", ForEachRegularFileTest6);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 7", ForEachRegularFileTest7);
    append<HeapAllocationErrorsTest>("forEachRegularFile test 8", ForEachRegularFileTest8);
}

void DirectoryTests::ConstructorTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory1");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    ISHTF_PASS();
}

void DirectoryTests::ForEachRegularFileTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory1");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const std::string& path)
        {
            files.emplace_back(path);
        },
        false
    );

    ISHTF_ABORT_IF_NEQ(files.size(), 1);
    ISHTF_FAIL_IF_NEQ(files[0], "../../TestData/Directory1/file1.txt");
    ISHTF_PASS();
}

void DirectoryTests::ForEachRegularFileTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory2");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const std::string& path)
        {
            files.emplace_back(path);
        },
        false
    );

    ISHTF_ABORT_IF_NEQ(files.size(), 2);
    ISHTF_FAIL_IF_NEQ(files[0], "../../TestData/Directory2/file1.txt");
    ISHTF_FAIL_IF_NEQ(files[1], "../../TestData/Directory2/file2.txt");
    ISHTF_PASS();
}

void DirectoryTests::ForEachRegularFileTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory3");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const std::string& path)
        {
            files.emplace_back(path);
        },
        false
    );

    ISHTF_FAIL_IF_NEQ(files.size(), 0);
    ISHTF_PASS();
}

void DirectoryTests::ForEachRegularFileTest4(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory4");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const std::string& path)
        {
            files.emplace_back(path);
        },
        false
        );

    ISHTF_ABORT_IF_NEQ(files.size(), 1);
    ISHTF_FAIL_IF_NEQ(files[0], "../../TestData/Directory4/file_1.txt");
    ISHTF_PASS();
}

void DirectoryTests::ForEachRegularFileTest5(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory1");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const std::string& path)
        {
            files.emplace_back(path);
        },
        true
    );

    ISHTF_ABORT_IF_NEQ(files.size(), 1);
    ISHTF_FAIL_IF_NEQ(files[0], "../../TestData/Directory1/file1.txt");
    ISHTF_PASS();
}

void DirectoryTests::ForEachRegularFileTest6(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory2");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const std::string& path)
        {
            files.emplace_back(path);
        },
        true
    );

    ISHTF_ABORT_IF_NEQ(files.size(), 2);
    ISHTF_FAIL_IF_NEQ(files[0], "../../TestData/Directory2/file1.txt");
    ISHTF_FAIL_IF_NEQ(files[1], "../../TestData/Directory2/file2.txt");
    ISHTF_PASS();
}

void DirectoryTests::ForEachRegularFileTest7(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory3");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const std::string& path)
        {
            files.emplace_back(path);
        },
        true
    );

    ISHTF_ABORT_IF_NEQ(files.size(), 1);
    ISHTF_FAIL_IF_NEQ(files[0], "../../TestData/Directory3/dir_1/file_1_1.txt");
    ISHTF_PASS();
}

void DirectoryTests::ForEachRegularFileTest8(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "Directory4");

    Ishiko::FileSystem::Directory directory(inputPath.string().c_str());

    std::vector<std::string> files;
    directory.forEachRegularFile(
        [&files](const std::string& path)
        {
            files.emplace_back(path);
        },
        true
        );

    ISHTF_ABORT_IF_NEQ(files.size(), 4);
    ISHTF_FAIL_IF_NEQ(files[0], "../../TestData/Directory4/dir_1/file_1_1.txt");
    ISHTF_FAIL_IF_NEQ(files[1], "../../TestData/Directory4/dir_2/file_2_1.txt");
    ISHTF_FAIL_IF_NEQ(files[2], "../../TestData/Directory4/dir_2/file_2_2.txt");
    ISHTF_FAIL_IF_NEQ(files[3], "../../TestData/Directory4/file_1.txt");
    ISHTF_PASS();
}
