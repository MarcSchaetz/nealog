#include "TestApi.h"
#include "nealog/Severity.h"
#include "nealog/Sink.h"
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string_view>

using namespace nealog;

constexpr const char* TAG           = "[Sink][FileSink]";
constexpr const char* TAG_THREADING = "[Sink][FileSink][Multithreading]";
constexpr bool TRUNCATE             = true;


auto getTmpPath() -> const std::filesystem::path
{
    return std::filesystem::temp_directory_path();
}



TEST_CASE("Type of FileSink is File", TAG)
{
    FileSink sink{getTmpPath(), TRUNCATE};
    requireResultEqualsExpected(sink.getType(), SinkType::File);
}



TEST_CASE("Create a FileSink from path", TAG)
{
    REQUIRE_NOTHROW(FileSink{getTmpPath(), TRUNCATE});
}



TEST_CASE("Create a FileSink from rvalue", TAG)
{
    REQUIRE_NOTHROW(FileSink{"/tmp/nealog_filesink_testfile", TRUNCATE});
}



TEST_CASE("Create a FileSink from std::string", TAG)
{
    const std::string path{"/tmp/nealog_filesink_testfile"};
    REQUIRE_NOTHROW(FileSink{path, TRUNCATE});
}



TEST_CASE("FileSink writes to and closes file on destroy", TAG)
{
    const std::string path{"/tmp/nealog_filesink_testfile"};
    {
        FileSink sink{path, TRUNCATE};
        sink.write(Severity::Error, std::string("Hello"));
        sink.write(Severity::Error, " World");
    }

    auto fileContent = readTextFromFile(path);

    requireResultEqualsExpected(fileContent, "Hello World");
}

auto createExistingFile(std::string_view filePath, std::string_view content) -> void
{
    std::ofstream existingFile{filePath.data()};
    existingFile << content;
    existingFile.close();
}

TEST_CASE("Don't truncate file if it exists", TAG)
{
    constexpr const char* path   = "/tmp/should_not_truncate";
    const std::string content    = "an existing line\n";
    const std::string additional = "a new line";
    createExistingFile(path, content);

    {
        FileSink sink{path};
        sink.write(Severity::Error, additional);
		sink.flush();
    }

    auto fileContent = readTextFromFile(path);
    requireResultEqualsExpected(fileContent, content + additional);
}
