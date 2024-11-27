// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "UtilitiesTests.hpp"
#include <Ishiko/FileSystem/FileSystemErrorCategory.hpp>
#include <Ishiko/FileSystem/Utilities.hpp>
#include <boost/filesystem/operations.hpp>

using namespace Ishiko;
using namespace Ishiko::FileSystem;

UtilitiesTests::UtilitiesTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "Utilities tests", context)
{
    append<HeapAllocationErrorsTest>("Exists test 1", ExistsTest1);
    append<HeapAllocationErrorsTest>("Exists test 2", ExistsTest2);
    append<HeapAllocationErrorsTest>("Exists test 3", ExistsTest3);
    append<HeapAllocationErrorsTest>("GetFileSize test 1", GetFileSizeTest1);
    append<HeapAllocationErrorsTest>("GetFileSize test 2", GetFileSizeTest2);
    append<HeapAllocationErrorsTest>("GetFileSize test 3", GetFileSizeTest3);
    append<HeapAllocationErrorsTest>("GetFileSize test 4", GetFileSizeTest4);
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
    append<HeapAllocationErrorsTest>("ReadFile test 4", ReadFileTest4);
    append<HeapAllocationErrorsTest>("ReadFile test 5", ReadFileTest5);
    append<HeapAllocationErrorsTest>("ReadFile test 6", ReadFileTest6);
    append<HeapAllocationErrorsTest>("ReadFile test 7", ReadFileTest7);
    append<HeapAllocationErrorsTest>("ReadFile test 8", ReadFileTest8);
    append<HeapAllocationErrorsTest>("ReadFile test 9", ReadFileTest9);
    append<HeapAllocationErrorsTest>("ReadFile test 10", ReadFileTest10);
    append<HeapAllocationErrorsTest>("ReadFile test 11", ReadFileTest11);
    append<HeapAllocationErrorsTest>("Copy test 1", CopyTest1);
    append<HeapAllocationErrorsTest>("Copy test 2", CopyTest2);
    append<HeapAllocationErrorsTest>("Copy test 3", CopyTest3);
    append<HeapAllocationErrorsTest>("Copy test 4", CopyTest4);
    append<HeapAllocationErrorsTest>("Copy test 5", CopyTest5);
    append<HeapAllocationErrorsTest>("Copy test 6", CopyTest6);
    append<HeapAllocationErrorsTest>("CopySingleFile test 1", CopySingleFileTest1);
    append<HeapAllocationErrorsTest>("CopySingleFile test 2", CopySingleFileTest2);
    append<HeapAllocationErrorsTest>("CopySingleFile test 3", CopySingleFileTest3);
#if ISHIKO_OS == ISHIKO_OS_WINDOWS
    append<HeapAllocationErrorsTest>("GetVolumeList test 1", GetVolumeListTest1);
#endif
}

void UtilitiesTests::ExistsTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    ISHIKO_TEST_FAIL_IF(Exists(inputPath.string().c_str()));
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ExistsTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    ISHIKO_TEST_FAIL_IF_NOT(Exists(inputPath.string().c_str()));
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ExistsTest3(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory());

    ISHIKO_TEST_FAIL_IF_NOT(Exists(inputPath.string().c_str()));
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::GetFileSizeTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    size_t fileSize = GetFileSize(inputPath.string().c_str());

    ISHIKO_TEST_FAIL_IF_NEQ(fileSize, 5);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::GetFileSizeTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    bool canary = false;
    try
    {
        size_t fileSize = GetFileSize(inputPath.string().c_str());
    }
    catch (const std::exception& e)
    {
        canary = true;
    }
    catch (...)
    {   
        ISHIKO_TEST_FAIL();
    }

    ISHIKO_TEST_FAIL_IF_NOT(canary);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::GetFileSizeTest3(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    Error error;
    size_t fileSize = GetFileSize(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(fileSize, 5);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::GetFileSizeTest4(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    Error error;
    size_t fileSize = GetFileSize(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::not_found);
    ISHIKO_TEST_FAIL_IF_NEQ(fileSize, 0);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::IsDirectoryTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory());

    Error error;
    bool isDir = IsDirectory(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(isDir);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::IsDirectoryTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    Error error;
    bool isDir = IsDirectory(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(isDir);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::IsDirectoryTest3(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    Error error;
    bool isDir = IsDirectory(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::not_found);
    ISHIKO_TEST_FAIL_IF(isDir);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::IsEmptyTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("empty.txt"));

    Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(empty);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::IsEmptyTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(empty);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::IsEmptyTest3(Test& test)
{
    boost::filesystem::path inputPath(test.context().getOutputPath("empty"));
    boost::filesystem::create_directory(inputPath);

    Ishiko::Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(empty);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::IsEmptyTest4(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataDirectory());

    Ishiko::Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(empty);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::IsEmptyTest5(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    Ishiko::Error error;
    bool empty = IsEmpty(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::not_found);
    ISHIKO_TEST_FAIL_IF(empty);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ToAbsolutePathTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    std::string currentPath = boost::filesystem::current_path().string();
#ifdef WIN32
    currentPath += "\\";
#else
    currentPath += "/";
#endif
    
    std::string absolutePath;
    ToAbsolutePath(inputPath.string().c_str(), absolutePath);

    ISHIKO_TEST_FAIL_IF_NEQ(absolutePath, currentPath + inputPath.string());
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ToAbsolutePathTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    std::string currentPath = boost::filesystem::current_path().string();
#ifdef WIN32
    currentPath += "\\";
#else
    currentPath += "/";
#endif

    std::string absolutePath;
    ToAbsolutePath(inputPath.string(), absolutePath);

    ISHIKO_TEST_FAIL_IF_NEQ(absolutePath, currentPath + inputPath.string());
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::CreateEmptyFileTest1(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("file1.txt");

    Ishiko::Error error;
    CreateEmptyFile(outputPath, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NOT(Exists(outputPath));
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::CreateEmptyFileTest2(Test& test)
{
    boost::filesystem::path outputPath = test.context().getOutputPath("file2.txt");

    Error error;
    CreateEmptyFile(outputPath, error);

    ISHIKO_TEST_ABORT_IF(error);
    
    CreateEmptyFile(outputPath, error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::already_exists);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest1(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    Error error;
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(bytesRead, 5);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest2(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    Error error;
    const int bufferSize = 10;
    char buffer[bufferSize];
    size_t bytesRead = ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(bytesRead, 0);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest3(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    Error error;
    const int bufferSize = 2;
    char buffer[bufferSize];
    size_t bytesRead = ReadFile(inputPath.string().c_str(), buffer, bufferSize, error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(error.code(), FileSystemErrorCategory::Value::buffer_overflow);
    ISHIKO_TEST_FAIL_IF_NEQ(bytesRead, 5);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest4(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    std::string bytes = ReadFile(inputPath.string().c_str());

    ISHIKO_TEST_FAIL_IF_NEQ(bytes, "hello");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest5(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    bool canary = false;
    try
    {
        std::string bytes = ReadFile(inputPath.string().c_str());
    }
    catch (const std::exception& e)
    {
        canary = true;
    }
    catch (...)
    {
        ISHIKO_TEST_FAIL();
    }

    ISHIKO_TEST_FAIL_IF_NOT(canary);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest6(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    Error error;
    std::string bytes = ReadFile(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(bytes, "hello");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest7(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    Error error;
    std::string bytes = ReadFile(inputPath.string().c_str(), error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(bytes, "");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest8(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    std::string bytes = ReadFile(inputPath);

    ISHIKO_TEST_FAIL_IF_NEQ(bytes, "hello");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest9(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    bool canary = false;
    try
    {
        std::string bytes = ReadFile(inputPath);
    }
    catch (const std::exception& e)
    {
        canary = true;
    }
    catch (...)
    {
        ISHIKO_TEST_FAIL();
    }

    ISHIKO_TEST_FAIL_IF_NOT(canary);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest10(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("file1.txt"));

    Error error;
    std::string bytes = ReadFile(inputPath, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_NEQ(bytes, "hello");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::ReadFileTest11(Test& test)
{
    boost::filesystem::path inputPath(test.context().getDataPath("doesnotexist"));

    Error error;
    std::string bytes = ReadFile(inputPath, error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(bytes, "");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::CopyTest1(Test& test)
{
    const char* output_filename = "UtilitiesTests_CopyTest1.txt";
    boost::filesystem::path source_path(test.context().getDataPath("file1.txt"));
    boost::filesystem::path destination_path(test.context().getOutputPath(output_filename));

    FileSystem::Copy(source_path, destination_path);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_filename);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::CopyTest2(Test& test)
{
    const char* output_filename = "UtilitiesTests_CopyTest2.txt";
    boost::filesystem::path source_path(test.context().getDataPath("file1.txt"));
    boost::filesystem::path destination_path(test.context().getOutputPath(
        std::string("subdir-CopyTest2/") + output_filename));

    try
    {
        FileSystem::Copy(source_path, destination_path);

        ISHIKO_TEST_FAIL();
    }
    catch (...)
    {
        ISHIKO_TEST_FAIL_IF(FileSystem::Exists(destination_path.parent_path()));
        ISHIKO_TEST_FAIL_IF(FileSystem::Exists(destination_path));
        ISHIKO_TEST_PASS();
    }
}

void UtilitiesTests::CopyTest3(Test& test)
{
    const char* output_subpath = "UtilitiesTests_CopyTest3";
    boost::filesystem::path source_path(test.context().getDataPath("Directory1"));
    boost::filesystem::path destination_path(test.context().getOutputPath(output_subpath));

    FileSystem::Copy(source_path, destination_path);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("UtilitiesTests_CopyTest3/file1.txt");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::CopyTest4(Test& test)
{
    const char* output_subpath = "UtilitiesTests_CopyTest4";
    boost::filesystem::path source_path(test.context().getDataPath("Directory2"));
    boost::filesystem::path destination_path(test.context().getOutputPath(output_subpath));

    FileSystem::Copy(source_path, destination_path);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("UtilitiesTests_CopyTest4/file1.txt");
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("UtilitiesTests_CopyTest4/file2.txt");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::CopyTest5(Test& test)
{
    const char* output_subpath = "subdir-CopyTest5/UtilitiesTests_CopyTest5";
    boost::filesystem::path source_path(test.context().getDataPath("Directory2"));
    boost::filesystem::path destination_path(test.context().getOutputPath(output_subpath));

    try
    {
        FileSystem::Copy(source_path, destination_path);

        ISHIKO_TEST_FAIL();
    }
    catch (...)
    {
        ISHIKO_TEST_FAIL_IF(FileSystem::Exists(destination_path.parent_path()));
        ISHIKO_TEST_FAIL_IF(FileSystem::Exists(destination_path));
        ISHIKO_TEST_PASS();
    }
}

void UtilitiesTests::CopyTest6(Test& test)
{
    const char* output_subpath = "subdir-CopyTest6/UtilitiesTests_CopyTest6";
    boost::filesystem::path source_path(test.context().getDataPath("Directory2"));
    boost::filesystem::path destination_path(test.context().getOutputPath(output_subpath));

    FileSystem::Copy(source_path, destination_path, CopyOption::create_directories);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("subdir-CopyTest6/UtilitiesTests_CopyTest6/file1.txt");
    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ("subdir-CopyTest6/UtilitiesTests_CopyTest6/file2.txt");
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::CopySingleFileTest1(Test& test)
{
    const char* output_filename = "UtilitiesTests_CopySingleFileTest1.txt";
    boost::filesystem::path source_path(test.context().getDataPath("file1.txt"));
    boost::filesystem::path destination_path(test.context().getOutputPath(output_filename));

    FileSystem::CopySingleFile(source_path, destination_path);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_filename);
    ISHIKO_TEST_PASS();
}

void UtilitiesTests::CopySingleFileTest2(Test& test)
{
    const char* output_filename = "UtilitiesTests_CopySingleFileTest2.txt";
    boost::filesystem::path source_path(test.context().getDataPath("file1.txt"));
    boost::filesystem::path destination_path(test.context().getOutputPath(
        std::string("subdir-CopySingleFileTest2/") + output_filename));

    try
    {
        FileSystem::CopySingleFile(source_path, destination_path);

        ISHIKO_TEST_FAIL();
    }
    catch (...)
    {
        ISHIKO_TEST_FAIL_IF(FileSystem::Exists(destination_path.parent_path()));
        ISHIKO_TEST_FAIL_IF(FileSystem::Exists(destination_path));
        ISHIKO_TEST_PASS();
    }
}

void UtilitiesTests::CopySingleFileTest3(Test& test)
{
    const char* output_subpath = "subdir-CopySingleFileTest3/UtilitiesTests_CopySingleFileTest3.txt";
    boost::filesystem::path source_path(test.context().getDataPath("file1.txt"));
    boost::filesystem::path destination_path(test.context().getOutputPath(output_subpath));

    FileSystem::CopySingleFile(source_path, destination_path, FileSystem::CopyOption::create_directories);

    ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_subpath);
    ISHIKO_TEST_PASS();
}

#if ISHIKO_OS == ISHIKO_OS_WINDOWS
void UtilitiesTests::GetVolumeListTest1(Test& test)
{
    Ishiko::Error error;
    std::vector<std::string> volumeNames;
    GetVolumeList(volumeNames, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_NOT(volumeNames.size() >= 1);

    for (const std::string& volumeName : volumeNames)
    {
        DWORD volumePathNamesLength = 5 * (MAX_PATH + 1) + 1;
        char* volumePathNames = new char[volumePathNamesLength];
        if (GetVolumePathNamesForVolumeNameA(volumeName.c_str(), volumePathNames, volumePathNamesLength,
            &volumePathNamesLength))
        {
            if ((volumePathNamesLength != 0) && (volumePathNames[0] != 0) && (strcmp(volumePathNames, "C:\\") == 0))
            {
                ISHIKO_TEST_PASS();
            }
        }
        delete[] volumePathNames;
    }
}
#endif
