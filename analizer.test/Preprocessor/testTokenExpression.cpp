
#include <string>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenExpression.h>
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenNewline.h>
#include <Preprocessor/TokenSpace.h>
#include <Preprocessor/Line.h>
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenExpression)

BOOST_AUTO_TEST_CASE(ShouldMatchWithNewlineEscape)
{
	// Given
	TokenExpression tex({"\\", isEol});
	list<shared_ptr<Token>> sequence = { 
		make_shared<TokenStub>("\\"), 
		make_shared<TokenNewline>(shared_ptr<Line>()) 
	};
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(get<0>(result));
	BOOST_REQUIRE(get<1>(result) == sequence.end());
}

list<shared_ptr<Token>> makeTokenList(const list<string> &texts)
{
	list<shared_ptr<Token>> tokens;
	transform(texts.begin(), texts.end(), back_inserter(tokens),
		[](const string &t){ return make_shared<TokenStub>(t); });
	return tokens;
}

BOOST_AUTO_TEST_CASE(ShouldMatchWithEmptyPattern)
{
	// Given
	TokenExpression tex({});
	auto sequence = makeTokenList({});
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(get<0>(result));
	BOOST_REQUIRE(get<1>(result) == sequence.end());
}

BOOST_AUTO_TEST_CASE(ShouldNotMatch)
{
	// Given
	TokenExpression tex({Not("a")});
	auto sequence = makeTokenList({"a"});
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(!get<0>(result));
}

BOOST_AUTO_TEST_CASE(ShouldMatchWithBraces)
{
	// Given
	TokenExpression tex({"{", Optional(Some(Not(Or("{", "}")))), "}"});
	auto sequence = makeTokenList({"{", "a", "b", "c", "}"});
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(get<0>(result));
	BOOST_REQUIRE(get<1>(result) == sequence.end());
}

BOOST_AUTO_TEST_CASE(ShouldNotMatchWithInnerBraces)
{
	// Given
	TokenExpression tex({"{", Optional(Some(Not(Or("{", "}")))), "}"});
	auto sequence = makeTokenList({"{", "a", "{", "c", "}"});
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(!get<0>(result));
}

BOOST_AUTO_TEST_CASE(ShouldIgnoreLastOptional)
{
	// Given
	TokenExpression tex({"{", Optional("}")});
	auto sequence = makeTokenList({"{"});
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(get<0>(result));
	BOOST_REQUIRE(get<1>(result) == sequence.end());
}

BOOST_AUTO_TEST_CASE(ShouldSkipOptional)
{
	// Given
	TokenExpression tex({"{", Optional("}"), "}"});
	auto sequence = makeTokenList({"{", "}", "x"});
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(get<0>(result));
	BOOST_REQUIRE_EQUAL((*get<1>(result))->getText(), "x");
}

BOOST_AUTO_TEST_CASE(ShouldParseOnlyOneOptional)
{
	// Given
	TokenExpression tex({"{", Optional("x"), "}"});
	auto sequence = makeTokenList({"{", "x", "x", "}"});
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(!get<0>(result));
}

BOOST_AUTO_TEST_CASE(ShouldMatchSomeNotEndl)
{
	// Given
	TokenExpression tex({Some(Not("x"))});
	auto sequence = makeTokenList({"a", "b", "c", "x"});
	// When
	auto result = tex.match(sequence.begin(), sequence.end());
	// Then
	BOOST_REQUIRE(get<0>(result));
	BOOST_REQUIRE_EQUAL((*get<1>(result))->getText(), "x");
}

BOOST_AUTO_TEST_SUITE_END()
