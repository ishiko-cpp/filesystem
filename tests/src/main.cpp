/*
    Copyright (c) 2020-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/ishiko-cpp/filesystem/blob/main/LICENSE.txt
*/

#include "BinaryFileTests.hpp"
#include "TextFileTests.h"
#include "DirectoryTests.h"
#include "UtilitiesTests.h"
#include <Ishiko/Tests/Core.hpp>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("IshikoFileSystem");

    theTestHarness.context().setTestDataDirectory("../../data");
    theTestHarness.context().setTestOutputDirectory("../../output");
    theTestHarness.context().setReferenceDataDirectory("../../reference");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<BinaryFileTests>();
    theTests.append<TextFileTests>();
    theTests.append<DirectoryTests>();
    theTests.append<UtilitiesTests>();

    return theTestHarness.run();
}
