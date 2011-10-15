
#include <iostream>
#include <list>
#include <boost/bind.hpp>
#include <boost/test/unit_test.hpp>
#include <Line.h>
#include <PreprocessorUncommenter.h>
#include <Token.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suitePreprocessorUncommenter)

struct testLL {
	list<Token> tokens;
	void parse(const Line *line, unsigned offset, unsigned size) {
		tokens.push_back(Token(line, offset, size));
	}
};

BOOST_AUTO_TEST_CASE(testNoComment)
{
	testLL ll;
	PreprocessorUncommenter pu(bind(&testLL::parse, &ll, _1, _2, _3));
	
	Line line(0, "1234567890", 0);
	pu.parse(&line);
	
	BOOST_REQUIRE_EQUAL(ll.tokens.size(), 1);
	BOOST_REQUIRE_EQUAL(ll.tokens.front().getText(), "1234567890");
}

BOOST_AUTO_TEST_CASE(testSimpleComment)
{
	testLL ll;
	PreprocessorUncommenter pu(bind(&testLL::parse, &ll, _1, _2, _3));
	
	Line line(0, "12345//67890", 0);
	pu.parse(&line);
	
	BOOST_REQUIRE_EQUAL(ll.tokens.size(), 1);
	BOOST_REQUIRE_EQUAL(ll.tokens.front().getText(), "12345");
}

BOOST_AUTO_TEST_CASE(testComentInQuote)
{
	testLL ll;
	PreprocessorUncommenter pu(bind(&testLL::parse, &ll, _1, _2, _3));
	
	Line line(0, "1234\"5//6\"7890", 0);
	pu.parse(&line);
	
	BOOST_REQUIRE_EQUAL(ll.tokens.size(), 1);
	BOOST_REQUIRE_EQUAL(ll.tokens.front().getText(), "1234\"5//6\"7890");
}

BOOST_AUTO_TEST_SUITE_END()
