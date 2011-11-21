
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenWord.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenWord)

BOOST_AUTO_TEST_CASE(testGetTextFromLine)
{
	const shared_ptr<const Line> line(new FileLine(10, "aaaxxxxxaaa", 0));
	const TokenWord token(line, 3, 8);
	BOOST_REQUIRE_EQUAL(token.getText(), "xxxxx");
}

BOOST_AUTO_TEST_CASE(testGetTextInString)
{
	const shared_ptr<const Line> line(new FileLine(10, "aaaxxxxxaaa", 0));
	const TokenWord token(line, 3, 8);
	BOOST_REQUIRE_EQUAL(token.getTextInString(), "aaaxxxxxaaa");
}

BOOST_AUTO_TEST_CASE(testGetTextInStringMarked)
{
	const shared_ptr<const Line> line(new FileLine(10, "aaaxxxxxaaa", 0));
	const TokenWord token(line, 3, 8);
	BOOST_REQUIRE_EQUAL(token.getTextInString(">", "<"), "aaa>xxxxx<aaa");
}

BOOST_AUTO_TEST_SUITE_END()
