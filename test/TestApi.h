#pragma once

#include "catch2/catch_test_macros.hpp"
#include "nealog/Logger.h"
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <string_view>


class TestFacade
{
    nealog::LoggerRegistry_st registry;

  public:
    auto getLogger(const std::string_view& name) -> std::shared_ptr<nealog::LoggerBase>
    {
        auto rootLogger = registry.getOrCreate(name.data());
        return rootLogger;
    }
};



template <typename Result, typename Expected>
inline auto requireResultEqualsExpected(Result result, Expected expected) -> void
{
    REQUIRE(result == expected);
}

template <typename T>
inline auto requirePointerNotNull(T* pointer) -> void
{
    REQUIRE(pointer != nullptr);
}

inline auto readTextFromFile(const std::string_view& path) -> std::string
{
    std::ifstream file{path.data()};
    std::string line{};
    std::ostringstream lines;
    while (std::getline(file, line))
    {
		lines << line << "\n";
    }

	auto str = lines.str();
	str.erase(str.length() -1);

    return str;
}
