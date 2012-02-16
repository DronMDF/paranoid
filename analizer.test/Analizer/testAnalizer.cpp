
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Analizer/Analizer.h>
#include <Preprocessor/Error.h>
#include "../Preprocessor/TestFile.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteAnalizer)

BOOST_AUTO_TEST_CASE(testConstruct)
{
	Analizer analizer;
	analizer(make_shared<TestFile>("test.cpp", list<string>()));
	BOOST_REQUIRE(analizer.getResult().empty());
}

BOOST_AUTO_TEST_SUITE_END()
