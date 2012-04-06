
#include <functional>
#include <boost/test/unit_test.hpp>
#include <Analizer/ExpressionIfDirective.h>
#include "../Assertions.h"
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteExpressionDefine)

BOOST_AUTO_TEST_CASE(testIf)
{
	ExpressionIfDirective exp({
		make_shared<TokenStub>("#if"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("1")});
	
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(exp.getUsedNames(), list<string>());
}

BOOST_AUTO_TEST_SUITE_END()
