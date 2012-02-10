
#include <string>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenExpression.h>
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenNewline.h>
#include <Preprocessor/TokenSpace.h>
#include <Preprocessor/Line.h>
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenExpression)

BOOST_AUTO_TEST_CASE(testMetched)
{
	TokenExpression tex({"\\", isEol});
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("\\")));
	auto line = make_shared<Line>(0, " ", static_cast<File *>(0));
	BOOST_REQUIRE(tex.match(make_shared<TokenNewline>(line)));
	BOOST_REQUIRE(tex.isMatched());
	BOOST_REQUIRE(!tex.match(make_shared<DummyToken>("more")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(!tex.isMatched());
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("\\")));
	BOOST_REQUIRE(!tex.isMatched());
}


BOOST_AUTO_TEST_CASE(testNot)
{
	TokenExpression tex({Not("a")});
	BOOST_REQUIRE(!tex.match(make_shared<DummyToken>("a")));
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("b")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testSome)
{
	TokenExpression tex({"a", Some("b"), "c"});
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("a")));
	// Any quantity of b
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("b")));
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("b")));
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("b")));
	
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("c")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testOptional)
{
	TokenExpression tex({"a", Optional("b"), "c"});
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("a")));
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("b")));
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("c")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("a")));
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("c")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testOptionalTail)
{
	TokenExpression tex({"a", Optional("b")});
	BOOST_REQUIRE(tex.match(make_shared<DummyToken>("a")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_SUITE_END()
