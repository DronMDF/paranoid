
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenSpace.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenSpace)

BOOST_AUTO_TEST_CASE(testGetTextAlwaysSpace)
{
	const shared_ptr<Line> line(new FileLine(10, "spaces      here", 0));
	const TokenSpace token(line, 6, 12);
	BOOST_REQUIRE_EQUAL(token.getText(), " ");
}

BOOST_AUTO_TEST_CASE(testGetTextInLine)
{
	const shared_ptr<Line> line(new FileLine(10, "spaces      here", 0));
	const TokenSpace token(line, 6, 12);
	BOOST_REQUIRE_EQUAL(token.getTextInString(">>>", "<<<"), "spaces>>>      <<<here");
}

BOOST_AUTO_TEST_SUITE_END()
