
#include <boost/test/unit_test.hpp>
#include <boost/range/algorithm/equal.hpp>
#include <CommandLine.h>

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suiteCommandLine)
	
BOOST_AUTO_TEST_CASE(testChaining)
{
	const char *argsrc[] = {"test", "-chain", "valid"};
	const char *argexpected[] = {"valid", 0};
	
	vector<const char *> argres = Chaining(3, argsrc);
	
	BOOST_REQUIRE_EQUAL_COLLECTIONS(argres.begin(), argres.end(), argexpected, argexpected + 2);
}

BOOST_AUTO_TEST_SUITE_END()
