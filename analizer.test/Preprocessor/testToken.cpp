
#include <memory>
#include <boost/test/unit_test.hpp>
#include <FileLine.h>
#include <Token.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteToken)

BOOST_AUTO_TEST_CASE(testGetTextFromLine)
{
	const shared_ptr<const Line> line(new FileLine(10, "aaaxxxxxaaa", 0));
	const Token token(line, 3, 5);
	BOOST_REQUIRE_EQUAL(token.getText(), "xxxxx");
}

BOOST_AUTO_TEST_CASE(testGetTextInString)
{
	const shared_ptr<const Line> line(new FileLine(10, "aaaxxxxxaaa", 0));
	const Token token(line, 3, 5);
	BOOST_REQUIRE_EQUAL(token.getTextInString(), "aaaxxxxxaaa");
}

BOOST_AUTO_TEST_CASE(testGetTextInStringMarked)
{
	const shared_ptr<const Line> line(new FileLine(10, "aaaxxxxxaaa", 0));
	const Token token(line, 3, 5);
	BOOST_REQUIRE_EQUAL(token.getTextInString(">", "<"), "aaa>xxxxx<aaa");
}

BOOST_AUTO_TEST_CASE(testGetEmptyText)
{
	// Special case - space token
	const Token token;
	BOOST_REQUIRE_EQUAL(token.getText(), " ");
}

BOOST_AUTO_TEST_SUITE_END()
