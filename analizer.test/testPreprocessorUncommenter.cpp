
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

BOOST_AUTO_TEST_SUITE(suitePreprocessorUncommenter)

struct fixtureLowLevelParser {
	PreprocessorUncommenter parser;
	list<string> values;
	
	fixtureLowLevelParser() 
		: parser(bind(&fixtureLowLevelParser::parse, this, _1, _2, _3)),
		   values()
	{
	}
	
	virtual ~fixtureLowLevelParser()
	{
	}
	
	void parse(const Line *line, unsigned, unsigned) {
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

BOOST_AUTO_TEST_SUITE_END()
