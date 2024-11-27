// SPDX-FileCopyrightText: 2000-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "BinaryFileTests.hpp"
#include "TextFileTests.hpp"
#include "DirectoryTests.hpp"
#include "UtilitiesTests.hpp"
#include <Ishiko/TestFramework/Core.hpp>
#include <exception>

using namespace Ishiko;

int main(int argc, char* argv[])
{
    try
    {
        TestHarness::CommandLineSpecification commandLineSpec;
        commandLineSpec.setDefaultValue("context.data", "../../data");
        commandLineSpec.setDefaultValue("context.output", "../../output");
        commandLineSpec.setDefaultValue("context.reference", "../../reference");

        Configuration configuration = commandLineSpec.createDefaultConfiguration();
        CommandLineParser::parse(commandLineSpec, argc, argv, configuration);

        TestHarness theTestHarness("Ishiko/C++ FileSystem Library Tests", configuration);

        TestSequence& theTests = theTestHarness.tests();
        theTests.append<BinaryFileTests>();
        theTests.append<TextFileTests>();
        theTests.append<DirectoryTests>();
        theTests.append<UtilitiesTests>();

        return theTestHarness.run();
    }
    catch (const std::exception& e)
    {
        return TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return TestApplicationReturnCode::exception;
    }
}
