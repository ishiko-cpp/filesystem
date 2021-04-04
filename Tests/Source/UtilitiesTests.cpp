/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "UtilitiesTests.h"
#include "Ishiko/FileSystem/Utilities.h"
#include "Ishiko/FileSystem/ErrorCategory.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

UtilitiesTests::UtilitiesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Utilities tests", environment)
{
    append<HeapAllocationErrorsTest>("Exists test 1", ExistsTest1);
    append<HeapAllocationErrorsTest>("Exists test 2", ExistsTest2);
    append<HeapAllocationErrorsTest>("Exists test 3", ExistsTest3);
    append<HeapAllocationErrorsTest>("GetFileSize test 1", GetFileSizeTest1);
    append<HeapAllocationErrorsTest>("IsDirectory test 1", IsDirectoryTest1);
    append<HeapAllocationErrorsTest>("IsDirectory test 2", IsDirectoryTest2);
    append<HeapAllocationErrorsTest>("IsDirectory test 3", IsDirectoryTest3);
    append<HeapAllocationErrorsTest>("IsEmpty test 1", IsEmptyTest1);
    append<HeapAllocationErrorsTest>("IsEmpty test 2", IsEmptyTest2);
    append<HeapAllocationErrorsTest>("IsEmpty test 3", IsEmptyTest3);
    append<HeapAllocationErrorsTest>("IsEmpty test 4", IsEmptyTest4);
    append<HeapAllocationErrorsTest>("IsEmpty test 5", IsEmptyTest5);
    append<HeapAllocationErrorsTest>("ToAbsolutePath test 1", ToAbsolutePathTest1);
    append<HeapAllocationErrorsTest>("ToAbsolutePath test 2", ToAbsolutePathTest2);
    append<HeapAllocationErrorsTest>("CreateEmptyFile test 1", CreateEmptyFileTest1);
    append<HeapAllocationErrorsTest>("CreateEmptyFile test 2", CreateEmptyFileTest2);
    append<HeapAllocationErrorsTest>("ReadFile test 1", ReadFileTest1);
    append<HeapAllocationErrorsTest>("ReadFile test 2", ReadFileTest2);
    append<HeapAllocationErrorsTest>("ReadFile test 3", ReadFileTest3);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    append<HeapAllocationErrorsTest>("GetVolumeList test 1", GetVolumeListTest1);
#endif
}

void UtilitiesTests::ExistsTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    ISHTF_FAIL_IF(Ishiko::FileSystem::Exists(inputPath.string().c_str()));
    ISHTF_PASS();
}

void UtilitiesTests::ExistsTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    ISHTF_FAIL_IF_NOT(Ishiko::FileSystem::Exists(inputPath.string().c_str()));
    ISHTF_PASS();
}

void UtilitiesTests::ExistsTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory());

    ISHTF_FAIL_IF_NOT(Ishiko::FileSystem::Exists(inputPath.string().c_str()));
    ISHTF_PASS();
}

void UtilitiesTests::GetFileSizeTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    size_t fileSize = Ishiko::FileSystem::GetFileSize(inputPath.string().c_str());

    ISHTF_FAIL_IF_NEQ(fileSize, 5);
    ISHTF_PASS();
}

void UtilitiesTests::IsDirectoryTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory());

    Ishiko::Error error;
    bool isDir = Ishiko::FileSystem::IsDirectory(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(isDir);
    ISHTF_PASS();
}

void UtilitiesTests::IsDirectoryTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    Ishiko::Error error;
    bool isDir = Ishiko::FileSystem::IsDirectory(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF(isDir);
    ISHTF_PASS();
}

void UtilitiesTests::IsDirectoryTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    Ishiko::Error error;
    bool isDir = Ishiko::FileSystem::IsDirectory(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), Ishiko::FileSystem::ErrorCategory::eNotFound);
    ISHTF_FAIL_IF(isDir);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("empty.txt"));

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(empty);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF(empty);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest3(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestOutputPath("empty"));
    boost::filesystem::create_directory(inputPath);

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(empty);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest4(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory());

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF(empty);
    ISHTF_PASS();
}

void UtilitiesTests::IsEmptyTest5(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    Ishiko::Error error;
    bool empty = Ishiko::FileSystem::IsEmpty(inputPath.string().c_str(), error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), Ishiko::FileSystem::ErrorCategory::eNotFound);
    ISHTF_FAIL_IF(empty);
    ISHTF_PASS();
}

void UtilitiesTests::ToAbsolutePathTest1(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    std::string currentPath = boost::filesystem::current_path().string();
#ifdef WIN32
    currentPath += "\\";
#else
    currentPath += "/";
#endif
    
    std::string absolutePath;
    Ishiko::FileSystem::ToAbsolutePath(inputPath.string().c_str(), absolutePath);

    ISHTF_FAIL_IF_NEQ(absolutePath, currentPath + inputPath.string());
    ISHTF_PASS();
}

void UtilitiesTests::ToAbsolutePathTest2(Ishiko::Tests::Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    std::string currentPath = boost::filesystem::current_path().string();
#ifdef WIN32
    currentPath += "\\";
#else
    currentPath += "/";
#endif

    std::string absolutePath;
    Ishiko::FileSystem::ToAbsolutePath(inputPath.string(), absolutePath);

    ISHTF_FAIL_IF_NEQ(absolutePath, currentPath + inputPath.string());
    ISHTF_PASS();
}

void UtilitiesTests::CreateEmptyFileTest1(Test& test)
{
    boost::filesystem::path outputPath = test.environment().getTestOutputPath("file1.txt");

    Ishiko::Error error;
    Ishiko::FileSystem::CreateEmptyFile(outputPath, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NOT(Ishiko::FileSystem::Exists(outputPath));
    ISHTF_PASS();
}

void UtilitiesTests::CreateEmptyFileTest2(Test& test)
{
    boost::filesystem::path outputPath = test.environment().getTestOutputPath("file2.txt");

    Ishiko::Error error;
    Ishiko::FileSystem::CreateEmptyFile(outputPath, error);

    ISHTF_ABORT_IF(error);
    
    Ishiko::FileSystem::CreateEmptyFile(outputPath, error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), Ishiko::FileSystem::ErrorCategory::eAlreadyExists);
    ISHTF_PASS();
}

void UtilitiesTests::ReadFileTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    Ishiko::Error error;
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF(error);
    ISHTF_FAIL_IF_NEQ(bytesRead, 5);
    ISHTF_PASS();
}

void UtilitiesTests::ReadFileTest2(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("doesnotexist"));

    Ishiko::Error error;
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(bytesRead, 0);
    ISHTF_PASS();
}

void UtilitiesTests::ReadFileTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataPath("file1.txt"));

    Ishiko::Error error;
    const int bufferSize = 2;
    char buffer[bufferSize];
    size_t bytesRead = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHTF_FAIL_IF_NOT(error);
    ISHTF_FAIL_IF_NEQ(error.condition().value(), Ishiko::FileSystem::ErrorCategory::eBufferOverflow);
    ISHTF_FAIL_IF_NEQ(bytesRead, 5);
    ISHTF_PASS();
}

#if ISHIKO_OS == ISHIKO_OS_WINDOWS
void UtilitiesTests::GetVolumeListTest1(Ishiko::Tests::Test& test)
{
    Ishiko::Error error;
    std::vector<std::string> volumeNames;
    Ishiko::FileSystem::GetVolumeList(volumeNames, error);

    ISHTF_FAIL_IF(error);
    ISHTF_ABORT_IF_NOT(volumeNames.size() >= 1);

    for (const std::string& volumeName : volumeNames)
    {
        DWORD volumePathNamesLength = 5 * (MAX_PATH + 1) + 1;
        char* volumePathNames = new char[volumePathNamesLength];
        if (GetVolumePathNamesForVolumeNameA(volumeName.c_str(), volumePathNames, volumePathNamesLength,
            &volumePathNamesLength))
        {
            if ((volumePathNamesLength != 0) && (volumePathNames[0] != 0) && (strcmp(volumePathNames, "C:\\") == 0))
            {
                ISHTF_PASS();
            }
        }
        delete[] volumePathNames;
    }
}
#endif
