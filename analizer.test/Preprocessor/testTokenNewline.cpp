
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenNewline.h>
#include <Preprocessor/FileLine.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenNewline)

BOOST_AUTO_TEST_CASE(testGetText)
{
	const shared_ptr<const Line> line(new FileLine(10, "aaaxxxxxaaa", 0));
	const TokenNewline token(line);
	BOOST_REQUIRE_EQUAL(token.getText(), "\n");
}

BOOST_AUTO_TEST_CASE(testGetTextInString)
{
	const shared_ptr<const Line> line(new FileLine(10, "aaaxxxxxaaa", 0));
	const TokenNewline token(line);
	BOOST_REQUIRE_EQUAL(token.getTextInString(), "aaaxxxxxaaa");
}

BOOST_AUTO_TEST_SUITE_END()
