
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenSpace.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenSpace)

BOOST_AUTO_TEST_CASE(testGetTextAlwaysSpace)
{
	auto line = make_shared<Line>(10, "spaces      here", static_cast<File *>(0));
	const TokenSpace token(line, 6, 12);
	BOOST_REQUIRE_EQUAL(token.getText(), " ");
}

BOOST_AUTO_TEST_SUITE_END()
