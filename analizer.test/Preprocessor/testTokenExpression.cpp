
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

BOOST_AUTO_TEST_CASE(testMetched)
{
	TokenExpression tex({"\\", isEol});
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("\\")));
	auto line = make_shared<Line>(0, " ", static_cast<File *>(0));
	BOOST_REQUIRE(tex.match(make_shared<TokenNewline>(line)));
	BOOST_REQUIRE(tex.isMatched());
	BOOST_REQUIRE(!tex.match(make_shared<TokenStub>("more")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(!tex.isMatched());
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("\\")));
	BOOST_REQUIRE(!tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testNot)
{
	TokenExpression tex({Not("a")});
	BOOST_REQUIRE(!tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testSome)
{
	TokenExpression tex({"a", Some("b"), "c"});
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	// Any quantity of b
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("c")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testOptional)
{
	TokenExpression tex({"a", Optional("b"), "c"});
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("c")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("c")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testOptionalTail)
{
	TokenExpression tex({"a", Optional("b")});
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testOptionalNot)
{
	TokenExpression tex({Optional(Not("a")), "a"});
	// first "b" is matched as first expression element
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.isMatched());
	
	// skip optional element of expression
	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testOptionalSome)
{
	TokenExpression tex({Optional(Some("a")), "b"});
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(testSomeOptional)
{
	TokenExpression tex({Some(Optional("a")), "b"});
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("a")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("b")));
	BOOST_REQUIRE(tex.isMatched());
}

BOOST_AUTO_TEST_CASE(ShouldMatchSomeNot)
{
	TokenExpression tex({"{", Optional(Some(Not("{"))), "}"});
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("{")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("}")));
	BOOST_REQUIRE(tex.isMatched());
	
	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("{")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("x")));
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("}")));
	BOOST_REQUIRE(tex.isMatched());

	tex.reset();
	BOOST_REQUIRE(tex.match(make_shared<TokenStub>("{")));
	BOOST_REQUIRE(!tex.match(make_shared<TokenStub>("{")));
}

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

BOOST_AUTO_TEST_SUITE_END()
