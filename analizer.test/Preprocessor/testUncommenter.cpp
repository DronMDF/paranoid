
#include <iostream>
#include <list>
#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <FileLine.h>
#include <Uncommenter.h>
#include <Token.h>
#include <Error.h>
#include "../Assertions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suitePPUncommenter)

struct fixtureLowLevelParser : public PPTokenizer {
	PPUncommenter parser;
	list<string> values;
	
	fixtureLowLevelParser() : parser(this), values() 
	{ }
	
	void parse(const shared_ptr<const Line> &line) {
		values.push_back(line->getText());
	}
};

BOOST_FIXTURE_TEST_CASE(testNoComment, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line(new FileLine(0, "1234567890", 0));
	parser.parse(line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234567890");
}

BOOST_FIXTURE_TEST_CASE(testSimpleComment, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line(new FileLine(0, "12345//67890", 0));
	parser.parse(line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "12345       ");
}

BOOST_FIXTURE_TEST_CASE(testComentInQuote, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line(new FileLine(0, "1234\"5//6\"7890", 0));
	parser.parse(line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234\"5//6\"7890");
}

BOOST_FIXTURE_TEST_CASE(testParenthesisOnelineComent, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line(new FileLine(0, "1234/*56*/7890", 0));
	parser.parse(line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234      7890");
}

BOOST_FIXTURE_TEST_CASE(testParenthesisOnelineComentTwice, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line(new FileLine(0, "1234/*56*/78/*9*/0", 0));
	parser.parse(line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234      78     0");
}

BOOST_FIXTURE_TEST_CASE(testOpenComment, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line(new FileLine(0, "1234/*567890", 0));
	parser.parse(line);
	
	BOOST_REQUIRE_EQUAL(values.front(), "1234        ");
}

BOOST_FIXTURE_TEST_CASE(testTwoLineComment, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line1(new FileLine(0, "1234/*567890", 0));
	parser.parse(line1);
	const shared_ptr<const Line> line2(new FileLine(0, "1234*/567890", 0));
	parser.parse(line2);

	list<string> expected = { "1234        ", "      567890"};
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(values, expected);
}

BOOST_FIXTURE_TEST_CASE(testEmptyLineInComment, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line1(new FileLine(0, "1234/*567890", 0));
	parser.parse(line1);
	const shared_ptr<const Line> line2(new FileLine(0, "", 0));
	parser.parse(line2);
	const shared_ptr<const Line> line3(new FileLine(0, "1234*/567890", 0));
	parser.parse(line3);

	list<string> expected = { "1234        ", "      567890"};
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(values, expected);
}

BOOST_FIXTURE_TEST_CASE(testSimpleSlash, fixtureLowLevelParser)
{
	const shared_ptr<const Line> line(new FileLine(0, "1234/567890", 0));
	parser.parse(line);

	BOOST_REQUIRE_EQUAL(values.front(), "1234/567890");
}

BOOST_FIXTURE_TEST_CASE(testWrongString, fixtureLowLevelParser)
{
	const string text = "const char *rl = \" \\t\\n\\\"\\\\'`@$><=;|&{(\";";
	const shared_ptr<const Line> line(new FileLine(0, text, 0));
	parser.parse(line);
	BOOST_REQUIRE_EQUAL(values.front(), text);
}

BOOST_FIXTURE_TEST_CASE(testMonoQuote, fixtureLowLevelParser)
{
	const string text = "else if (quote_char == '\"')";
	const shared_ptr<const Line> line(new FileLine(0, text, 0));
	parser.parse(line);
	BOOST_REQUIRE_EQUAL(values.front(), text);
}

const string SSEL = "\033[1;31m";
const string ESEL = "\033[0m";

BOOST_FIXTURE_TEST_CASE(testOpenQuote, fixtureLowLevelParser)
{
	const string text = "print \"xxx;";
	const shared_ptr<const Line> line(new FileLine(0, text, 0));
	auto pred = [&SSEL, &ESEL](const Error &e) {
		return e.what() == "<unknown>:0 error: Open quote\nprint " + SSEL + "\"xxx;" + ESEL;
	};
	BOOST_REQUIRE_EXCEPTION(parser.parse(line), Error, pred);
}

BOOST_AUTO_TEST_SUITE_END()
