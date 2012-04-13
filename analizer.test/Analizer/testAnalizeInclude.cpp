
#include <boost/test/unit_test.hpp>
#include <Analizer/AnalizeInclude.h>
#include <Preprocessor/TokenInclude.h>
#include "../Assertions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteAnalizeInclude)

BOOST_AUTO_TEST_CASE(testTrivial)
{
	AnalizeInclude ai;
	auto include = make_shared<TokenInclude>(list<shared_ptr<Token>>());
	ai.checkToken(include);
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(ai.getUnused(), {include});
}

BOOST_AUTO_TEST_SUITE_END()
