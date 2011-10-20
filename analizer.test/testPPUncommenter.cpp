
#include <iostream>
#include <list>
#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <FileLine.h>
#include <PPUncommenter.h>
#include <Token.h>
#include "Assertions.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suitePPUncommenter)

struct fixtureLowLevelParser : public PPTokenizer {
	PPUncommenter parser;
	list<string> values;
	
	fixtureLowLevelParser() : parser(this), values() 
	{ }
	
	void parse(const Line *line) {
		values.push_back(line->getText());
	}
};

BOOST_FIXTURE_TEST_CASE(testNoComment, fixtureLowLevelParser)
{
	FileLine line(0, "1234567890", 0);
	parser.parse(&line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234567890");
}

BOOST_FIXTURE_TEST_CASE(testSimpleComment, fixtureLowLevelParser)
{
	FileLine line(0, "12345//67890", 0);
	parser.parse(&line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "12345       ");
}

BOOST_FIXTURE_TEST_CASE(testComentInQuote, fixtureLowLevelParser)
{
	FileLine line(0, "1234\"5//6\"7890", 0);
	parser.parse(&line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234\"5//6\"7890");
}

BOOST_FIXTURE_TEST_CASE(testParenthesisOnelineComent, fixtureLowLevelParser)
{
	FileLine line(0, "1234/*56*/7890", 0);
	parser.parse(&line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234      7890");
}

BOOST_FIXTURE_TEST_CASE(testParenthesisOnelineComentTwice, fixtureLowLevelParser)
{
	FileLine line(0, "1234/*56*/78/*9*/0", 0);
	parser.parse(&line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234      78     0");
}

BOOST_FIXTURE_TEST_CASE(testOpenComment, fixtureLowLevelParser)
{
	FileLine line(0, "1234/*567890", 0);
	parser.parse(&line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234        ");
}

BOOST_FIXTURE_TEST_CASE(testTwoLineComment, fixtureLowLevelParser)
{
	const FileLine line1(0, "1234/*567890", 0);
	parser.parse(&line1);
	const FileLine line2(0, "1234*/567890", 0);
	parser.parse(&line2);

	list<string> expected = { "1234        ", "      567890"};
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(values, expected);
}

BOOST_FIXTURE_TEST_CASE(testSimpleSlash, fixtureLowLevelParser)
{
	const FileLine line(0, "1234/567890", 0);
	parser.parse(&line);

	BOOST_REQUIRE_EQUAL(values.front(), "1234/567890");
}

BOOST_AUTO_TEST_SUITE_END()
