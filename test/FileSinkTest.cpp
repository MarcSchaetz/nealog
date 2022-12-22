#include "TestApi.h"
#include "nealog/Severity.h"
#include "nealog/Sink.h"
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <ios>

using namespace nealog;

constexpr const char* TAG           = "[Sink][FileSink]";
constexpr const char* TAG_THREADING = "[Sink][FileSink][Multithreading]";


auto getTmpPath() -> const std::filesystem::path
{
    return std::filesystem::temp_directory_path();
}



TEST_CASE("Type of FileSink is File", TAG)
{
    FileSink sink{getTmpPath()};
    requireResultEqualsExpected(sink.getType(), SinkType::File);
}



TEST_CASE("Create a FileSink from path", TAG)
{
    REQUIRE_NOTHROW(FileSink{getTmpPath()});
}



TEST_CASE("Create a FileSink from rvalue", TAG)
{
    REQUIRE_NOTHROW(FileSink{"/tmp/nealog_filesink_testfile"});
}



TEST_CASE("Create a FileSink from std::string", TAG)
{
    const std::string path{"/tmp/nealog_filesink_testfile"};
    REQUIRE_NOTHROW(FileSink{path});
}



TEST_CASE("FileSink writes to and closes file on destroy", TAG)
{
    const std::string path{"/tmp/nealog_filesink_testfile"};
    {
        FileSink sink{path};
        sink.write(Severity::Error, std::string("Hello"));
        sink.write(Severity::Error, " World");
    }

	auto fileContent = readTextFromFile(path);

    requireResultEqualsExpected(fileContent, "Hello World");
}

