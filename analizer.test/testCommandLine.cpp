
#include <boost/test/unit_test.hpp>
#include <CommandLine.h>
#include "Assertions.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suiteCommandLine)
	
BOOST_AUTO_TEST_CASE(testChaining)
{
	vector<const char *> argsrc = {"test", "-chain", "valid"};
	auto argres = Chaining(argsrc.size(), &argsrc[0]);
	
	list<const char *> argexpected = {"valid", 0};
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(argres, argexpected);
}

BOOST_AUTO_TEST_SUITE_END()
