
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenSpace.h>
#include <Preprocessor/Line.h>
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenPredicate)

BOOST_AUTO_TEST_CASE(testTextMatch)
{
	TokenPredicate pred("test");
	BOOST_REQUIRE(pred(shared_ptr<Token>(new DummyToken("test"))));
	BOOST_REQUIRE(!pred(shared_ptr<Token>(new DummyToken("text"))));
}

BOOST_AUTO_TEST_CASE(testNot)
{
	TokenPredicate predicate = Not("test");
	BOOST_REQUIRE(!predicate(shared_ptr<Token>(new DummyToken("test"))));
	BOOST_REQUIRE(predicate(shared_ptr<Token>(new DummyToken("text"))));
}

BOOST_AUTO_TEST_CASE(testIsSpace)
{
	shared_ptr<const Line> line_ptr(new Line(0, " ", 0));
	BOOST_REQUIRE(isSpace(shared_ptr<Token>(new TokenSpace(line_ptr, 0, 1))));
	BOOST_REQUIRE(!isSpace(shared_ptr<Token>(new DummyToken("text"))));
}

BOOST_AUTO_TEST_SUITE_END()
