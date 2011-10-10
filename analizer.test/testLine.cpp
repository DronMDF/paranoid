

#include <sstream>
#include <boost/test/unit_test.hpp>

#include <File.h>
#include <Line.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteLine)

BOOST_AUTO_TEST_CASE(GetFilePointer)
{
	istringstream in("");
	File file(in);
	Line line(10, "test", &file);
	BOOST_REQUIRE_EQUAL(line.getFile(), &file);
}

BOOST_AUTO_TEST_SUITE_END()
