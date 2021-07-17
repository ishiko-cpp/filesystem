/*
    Copyright (c) 2020-2021 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "TextFileTests.h"
#include "DirectoryTests.h"
#include "UtilitiesTests.h"
#include <Ishiko/Tests/Core.h>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoFileSystem");

    theTestHarness.environment().setTestDataDirectory("../../TestData");
    theTestHarness.environment().setTestOutputDirectory("../../TestOutput");
    theTestHarness.environment().setReferenceDataDirectory("../../ReferenceData");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<TextFileTests>();
    theTests.append<DirectoryTests>();
    theTests.append<UtilitiesTests>();

    return theTestHarness.run();
}
