

#include <boost/test/unit_test.hpp>
#include <Locator.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteError)

BOOST_AUTO_TEST_CASE(testLocateLine)
{
	Locator locator;
	locator.setLineNumber(10);
	BOOST_REQUIRE_EQUAL(locator.toString(), "in file <unknown>:10");
}

BOOST_AUTO_TEST_SUITE_END()
