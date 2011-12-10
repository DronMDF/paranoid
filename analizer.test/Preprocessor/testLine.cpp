

#include <sstream>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include "TestFile.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteFileLine)

BOOST_AUTO_TEST_CASE(testGetLocation)
{
	TestFile file("test.cpp", {});
	Line line(10, "test", &file);
	BOOST_REQUIRE_EQUAL(line.getLocation(), "test.cpp:10");
}

BOOST_AUTO_TEST_SUITE_END()
