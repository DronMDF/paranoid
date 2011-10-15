
#include <boost/regex.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suiteBoost)

BOOST_AUTO_TEST_CASE(testRegexMatchExample)
{
	const regex re("(\\d{4}[- ]){3}\\d{4}");
	BOOST_REQUIRE(regex_match("1234 1234 1234 1235", re));
}
	
BOOST_AUTO_TEST_CASE(testRegexMatch)
{
	const string text("xxxabcdefijkxxx");
	const regex re("(def)");
	smatch what;
	BOOST_REQUIRE(regex_search(text, what, re));
	BOOST_REQUIRE_EQUAL(what.str(1), "def");
	BOOST_REQUIRE_EQUAL(what.position(1), 6);
	BOOST_REQUIRE_EQUAL(what.length(1), 3);
}

BOOST_AUTO_TEST_SUITE_END();
