
#include <iostream>
#include <list>
#include <boost/bind.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <Line.h>
#include <PreprocessorUncommenter.h>
#include <Token.h>
#include "Assertions.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suitePreprocessorUncommenter)

void CUSTOM_REQUIRE_EQUAL_TOKENS(const list<Token> &tokens, const list<string> &expected)
{
	list<string> values;
	transform(tokens, back_inserter(values), [](const Token &t){ return t.getText(); });
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(values, expected);
}

struct fixtureLowLevelParser {
	PreprocessorUncommenter parser;
	list<Token> tokens;
	
	fixtureLowLevelParser() 
		: parser(bind(&fixtureLowLevelParser::parse, this, _1, _2, _3))
	{
	}
	
	void parse(const Line *line, unsigned offset, unsigned size) {
		tokens.push_back(Token(line, offset, size));
	}
};

BOOST_FIXTURE_TEST_CASE(testNoComment, fixtureLowLevelParser)
{
	Line line(0, "1234567890", 0);
	parser.parse(&line);
	
	list<string> expected = { "1234567890" };
	CUSTOM_REQUIRE_EQUAL_TOKENS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testSimpleComment, fixtureLowLevelParser)
{
	Line line(0, "12345//67890", 0);
	parser.parse(&line);
	
	list<string> expected = { "12345" };
	CUSTOM_REQUIRE_EQUAL_TOKENS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testComentInQuote, fixtureLowLevelParser)
{
	Line line(0, "1234\"5//6\"7890", 0);
	parser.parse(&line);
	
	list<string> expected = { "1234\"5//6\"7890" };
	CUSTOM_REQUIRE_EQUAL_TOKENS(tokens, expected);
}

BOOST_AUTO_TEST_SUITE_END()
