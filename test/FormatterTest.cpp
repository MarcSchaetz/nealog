#include "nealog/Formatter.h"
#include "TestApi.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace nealog;

constexpr const char* TAG = "[Formatter]";

class FormatterTestFixture
{
  public:
    FormatterTestFixture()
    {
    }

    Formatter formatter;
};

TEST_CASE_METHOD(FormatterTestFixture, "should concat strings", TAG)
{
    const std::string EXPECTED = "Hello world";
    std::string result         = formatter.format("Hello {}", "world");
    requireResultEqualsExpected(result, EXPECTED);
}



TEST_CASE_METHOD(FormatterTestFixture, "should concat string and int", TAG)
{
    const std::string EXPECTED = "one is 1";
    std::string result         = formatter.format("one is {}", 1);
    requireResultEqualsExpected(result, EXPECTED);
}



TEST_CASE_METHOD(FormatterTestFixture, "should concat string and float", TAG)
{
    const std::string EXPECTED = "one is 1.0";
    std::string result         = formatter.format("one is {:.1f}", 1.0f);
    requireResultEqualsExpected(result, EXPECTED);
}
