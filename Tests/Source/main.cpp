/*
    Copyright (c) 2020 Xavier Leclercq
    Released under the MIT License
    See https://github.com/Ishiko-cpp/FileSystem/blob/master/LICENSE.txt
*/

#include "UtilitiesTests.h"
#include <Ishiko/TestFramework/TestFrameworkCore.h>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoFileSystem");

    theTestHarness.environment().setTestDataDirectory("../../TestData");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<UtilitiesTests>();

    return theTestHarness.run();
}
