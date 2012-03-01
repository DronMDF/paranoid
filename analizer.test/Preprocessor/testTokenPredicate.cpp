
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenNewline.h>
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenSpace.h>
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenPredicate)

BOOST_AUTO_TEST_CASE(testTextMatch)
{
	TokenPredicate pred("test");
	BOOST_REQUIRE(pred(make_shared<TokenStub>("test")));
	BOOST_REQUIRE(!pred(make_shared<TokenStub>("text")));
}

BOOST_AUTO_TEST_CASE(testNot)
{
	TokenPredicate predicate = Not("test");
	BOOST_REQUIRE(!predicate(make_shared<TokenStub>("test")));
	BOOST_REQUIRE(predicate(make_shared<TokenStub>("text")));
}

BOOST_AUTO_TEST_CASE(testIsSpace)
{
	auto line_ptr = make_shared<Line>(0, " ", static_cast<const File *>(0));
	BOOST_REQUIRE(isSpace(make_shared<TokenSpace>(line_ptr, 0, 1)));
	BOOST_REQUIRE(!isSpace(make_shared<TokenStub>("text")));
}

BOOST_AUTO_TEST_CASE(testIsEol)
{
	auto line_ptr = make_shared<Line>(0, " ", static_cast<const File *>(0));
	BOOST_REQUIRE(isEol(make_shared<TokenNewline>(line_ptr)));
	BOOST_REQUIRE(!isEol(make_shared<TokenStub>("text")));
}

BOOST_AUTO_TEST_SUITE_END()
