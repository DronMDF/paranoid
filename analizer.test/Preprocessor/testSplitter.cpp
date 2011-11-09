
#include <boost/bind.hpp>
#include <boost/test/unit_test.hpp>
#include <FileLine.h>
#include <Splitter.h>
#include <Token.h>
#include "../Assertions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteSplitter)

struct fixtureTokenStorage {
	Splitter splitter;
	list<string> values;
	
	fixtureTokenStorage() 
		: splitter([&](const std::shared_ptr<const Token> &t) { values.push_back(t->getText()); }),
		  values()
	{}
	
	virtual ~fixtureTokenStorage();
};

fixtureTokenStorage::~fixtureTokenStorage() = default;

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
