
#include <boost/test/unit_test.hpp>
#include <Analizer/ExpressionIfBlock.h>
#include <Analizer/ExpressionIfDirective.h>
#include <Analizer/ExpressionDefine.h>
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteExpressionIfBlock)

BOOST_AUTO_TEST_CASE(ShouldDetectIncludeGuard)
{
	// Given
	list<shared_ptr<Token>> ifndef_list = {
		make_shared<TokenStub>("#ifndef"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("FILE_H"),
	};
	list<shared_ptr<Token>> define_list = {
		make_shared<TokenStub>("#define"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("FILE_H"),
	};
	ExpressionIfBlock exp({
		make_shared<ExpressionIfDirective>(ifndef_list),
		make_shared<ExpressionDefine>(define_list),
		make_shared<TokenStub>("#endif")
	});
	// Then
	BOOST_REQUIRE_EQUAL(exp.getIncludeGuardName(), "FILE_H");
}

BOOST_AUTO_TEST_SUITE_END()
