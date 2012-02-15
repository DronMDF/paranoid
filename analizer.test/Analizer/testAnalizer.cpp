
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Analizer/Analizer.h>
#include "../Preprocessor/TestFile.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteAnalizer)

BOOST_AUTO_TEST_CASE(testConstruct)
{
	Analizer analizer;
	analizer(make_shared<TestFile>("test.cpp", list<string>()));
}

BOOST_AUTO_TEST_SUITE_END()
