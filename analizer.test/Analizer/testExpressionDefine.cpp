
#include <boost/test/unit_test.hpp>
#include <Analizer/ExpressionDefine.h>
#include "../Preprocessor/DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteExpressionDefine)

BOOST_AUTO_TEST_CASE(testUsedNames)
{
	ExpressionDefine ex({
		make_shared<DummyToken>("#define"),
		make_shared<DummyToken>(" "),
		make_shared<DummyToken>("a"),
		make_shared<DummyToken>(" "),
		make_shared<DummyToken>("0")});

	BOOST_REQUIRE(ex.getUsedNames().empty());
}

BOOST_AUTO_TEST_SUITE_END()
