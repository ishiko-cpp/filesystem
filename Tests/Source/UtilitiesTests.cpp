/*
    Copyright (c) 2020 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "UtilitiesTests.h"
#include "Ishiko/FileSystem/Utilities.h"

using namespace Ishiko::Tests;

UtilitiesTests::UtilitiesTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Utilities tests", environment)
{
    append<HeapAllocationErrorsTest>("ReadFile test 1", ReadFileTest1);
}

void UtilitiesTests::ReadFileTest1(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "file1.txt");

    const int bufferSize = 10;
    char buffer[bufferSize];
    int err = Ishiko::FileSystem::ReadFile(inputPath.string().c_str(), buffer, bufferSize);

    ISHTF_FAIL_IF_NEQ(err, 5);
    ISHTF_PASS();
}
