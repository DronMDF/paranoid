
#include <boost/bind.hpp>
#include <boost/test/unit_test.hpp>
#include <FileLine.h>
#include <PPSplitter.h>
#include <Token.h>
#include "Assertions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suitePPSplitter)

struct fixtureTokenStorage {
	PPSplitter splitter;
	list<string> values;
	
	fixtureTokenStorage() 
		: splitter(bind(&fixtureTokenStorage::add_token, this, _1)),
		  values()
	{}
	
	virtual ~fixtureTokenStorage()
	{}
	
	void add_token(Token token) {
		values.push_back(token.getText());
	}
};

BOOST_FIXTURE_TEST_CASE(testMonolith, fixtureTokenStorage)
{
	shared_ptr<const Line> line(new FileLine(0, "solid", 0));
	splitter.parse(line);
	
	list<string> expected = { "solid" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(values, expected);
}

BOOST_FIXTURE_TEST_CASE(testTwoWord, fixtureTokenStorage)
{
	shared_ptr<const Line> line(new FileLine(0, "two word", 0));
	splitter.parse(line);
	
	list<string> expected = { "two", " ", "word" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(values, expected);
}

BOOST_AUTO_TEST_SUITE_END()
