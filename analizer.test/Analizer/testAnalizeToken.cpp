
#include <boost/test/unit_test.hpp>
#include <Analizer/AnalizeToken.h>
#include <Analizer/ExpressionDefine.h>
#include "../Assertions.h"
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteAnalizeUsed)

BOOST_AUTO_TEST_CASE(testGatherUsedNames)
{
	const list<shared_ptr<Token>> tokens = {
		make_shared<TokenStub>("#define"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("A"),
		make_shared<TokenStub>(" "),
		make_shared<TokenStub>("B")
	};
	
	AnalizeToken at;
	at.checkToken(make_shared<ExpressionDefine>(tokens));

	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(at.getUsedNames(), {"B"});
}

BOOST_AUTO_TEST_SUITE_END()
