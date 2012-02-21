
#include <boost/test/unit_test.hpp>
#include <Analizer/ExpressionDefine.h>
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteExpressionDefine)

BOOST_AUTO_TEST_CASE(testUsedNames)
{
	ExpressionDefine ex({
		make_shared<TokenStub>("#define"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("a"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("0")});

	BOOST_REQUIRE(ex.getUsedNames().empty());
}

BOOST_AUTO_TEST_SUITE_END()
