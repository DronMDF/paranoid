
#include <boost/test/unit_test.hpp>
#include <Preprocessor/IncludeLocator.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludeLocator)

BOOST_AUTO_TEST_CASE(testSystemLocate)
{
	struct testIncludeLocator : public IncludeLocator {
		testIncludeLocator() : IncludeLocator({"-isystem", "/Include"}) {}
		bool isExists(const string &include) const {
			return include == "/Include/foo.h";
		}
	} locator;
	
	BOOST_REQUIRE_EQUAL(locator.locate("", "foo.h", true), "/Include/foo.h");
}

BOOST_AUTO_TEST_CASE(testNotExists)
{
	struct testIncludeLocator : public IncludeLocator {
		testIncludeLocator() : IncludeLocator({}) {}
		bool isExists(const string &include) const {
			return false;
		}
	} locator;
	
	BOOST_REQUIRE_THROW(locator.locate("", "foo.h", true), exception);
}

BOOST_AUTO_TEST_SUITE_END()
