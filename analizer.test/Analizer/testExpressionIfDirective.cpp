
#include <functional>
#include <boost/test/unit_test.hpp>
#include <Analizer/ExpressionIfDirective.h>
#include "../Assertions.h"
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteExpressionDefine)

ExpressionIfDirective createIfDirective(const list<string> &texts)
{
	list<shared_ptr<Token>> tokens;
	transform(texts.begin(), texts.end(), back_inserter(tokens),
		[](const string &t){ return make_shared<TokenStub>(t); });
	return ExpressionIfDirective(tokens);
}
	
BOOST_AUTO_TEST_CASE(testIf)
{
	ExpressionIfDirective exp = createIfDirective({"#if", " ", "1"});
	BOOST_REQUIRE(exp.getUsedNames().empty());
	BOOST_REQUIRE(exp.getDeclaredNames().empty());
}

BOOST_AUTO_TEST_CASE(testIfdef)
{
	ExpressionIfDirective exp = createIfDirective({"#ifdef", " ", "A"});
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(exp.getUsedNames(), { "A" });
	BOOST_REQUIRE(exp.getDeclaredNames().empty());
}

BOOST_AUTO_TEST_CASE(ShouldReturnDirective)
{
	ExpressionIfDirective exp = createIfDirective({"#ifndef", " ", "FILE_H"});
	BOOST_REQUIRE_EQUAL(exp.getDirective(), "#ifndef");
}

BOOST_AUTO_TEST_SUITE_END()
