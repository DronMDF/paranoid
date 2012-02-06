
#include <string>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenExpression.h>
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenNewline.h>
#include <Preprocessor/Line.h>
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenExpression)

BOOST_AUTO_TEST_CASE(testSimple)
{
	TokenExpression tex({"\\", isEol});
	BOOST_REQUIRE(tex.match(shared_ptr<Token>(new DummyToken("\\"))));
	const shared_ptr<const Line> line_ptr(new Line(0, " ", 0));
	BOOST_REQUIRE(tex.match(shared_ptr<Token>(new TokenNewline(line_ptr))));
	BOOST_REQUIRE(tex.isMatched());
	BOOST_REQUIRE(!tex.match(shared_ptr<Token>(new DummyToken("more"))));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(!tex.isMatched());
	BOOST_REQUIRE(tex.match(shared_ptr<Token>(new DummyToken("\\"))));
	BOOST_REQUIRE(!tex.isMatched());
}

BOOST_AUTO_TEST_SUITE_END()
