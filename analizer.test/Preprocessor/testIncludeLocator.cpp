
#include <boost/test/unit_test.hpp>
#include <Preprocessor/IncludeLocator.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludeLocator)

BOOST_AUTO_TEST_CASE(testGetText)
{
	struct testIncludeLocator : public IncludeLocator {
		testIncludeLocator() : IncludeLocator({}) {}
		virtual void readSpec(const vector<const char *> &) {}
	} locator;
}

BOOST_AUTO_TEST_SUITE_END()
