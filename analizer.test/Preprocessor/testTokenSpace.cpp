
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenSpace.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenSpace)

BOOST_AUTO_TEST_CASE(testGetTextAlwaysSpace)
{
	BOOST_REQUIRE_EQUAL(TokenSpace().getText(), " ");
}

BOOST_AUTO_TEST_SUITE_END()
