
#include <string>
#include <initializer_list>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenExpression.h>
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenExpression)

void CUSTOM_REQUIRE_EQUAL_TEX(/*const*/ TokenExpression &tex, const string &text, 
			      const TokenExpression::status status)
{
	shared_ptr<Token> tok(new DummyToken(text));
	BOOST_REQUIRE(tex.match(tok) == status);
}

BOOST_AUTO_TEST_CASE(testSimple)
{
	TokenExpression tex({"a", "b"});
	CUSTOM_REQUIRE_EQUAL_TEX(tex, "x", TokenExpression::status::error);
	//CUSTOM_REQUIRE_EQUAL_TEX(tex, "a", TokenExpression::continue);
	//CUSTOM_REQUIRE_EQUAL_TEX(tex, "b", TokenExpression::last);
}

BOOST_AUTO_TEST_SUITE_END()
