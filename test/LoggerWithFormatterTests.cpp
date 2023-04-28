#include "nealog/Formatter.h"
#include "nealog/Logger.h"
#include "TestApi.h"
#include "catch2/matchers/catch_matchers.hpp"
#include "nealog/Severity.h"
#include "nealog/Sink.h"
#include <sstream>

using namespace nealog;

constexpr const char* TAG = "[Formatter][Integration]";



TEST_CASE("PatternFormatter substitutes name of logger", TAG)
{
	Logger logger{"michel"};
	logger.setFormatter(PatternFormatter("%(name): lorem"));

	std::ostringstream stream{};
	auto sink = SinkFactory::createStreamSink(stream);
	logger.addSink(sink);

	logger.info("message will not be seen");

	requireResultEqualsExpected(stream.str(), "michel: lorem");
}



TEST_CASE("PatternFormatter substitutes severity name and msg of logger", TAG)
{
	Logger logger{"michel"};

	std::ostringstream stream{};
	auto sink = SinkFactory::createStreamSink(stream);
	logger.addSink(sink);
	logger.setSeverity(Severity::Info);
	logger.setFormatter(PatternFormatter("%(levelname): %(msg)"));

	logger.info("message here");

	requireResultEqualsExpected(stream.str(), "Info: message here");
}



TEST_CASE("PatternFormatter substitutes severity number and msg of logger", TAG)
{
	Logger logger{"michel"};

	std::ostringstream stream{};
	auto sink = SinkFactory::createStreamSink(stream);
	logger.addSink(sink);
	logger.setSeverity(Severity::Debug);
	logger.setFormatter(PatternFormatter("%(levelno): %(msg)"));

	logger.info("message here");

	requireResultEqualsExpected(stream.str(), "1: message here");
}
