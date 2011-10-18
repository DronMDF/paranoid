

#include <sstream>
#include <boost/test/unit_test.hpp>

#include <File.h>
#include <FileLine.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteFileLine)

BOOST_AUTO_TEST_CASE(GetFilePointer)
{
	istringstream in("");
	File file(in);
	FileLine line(10, "test", &file);
	BOOST_REQUIRE_EQUAL(line.getFile(), &file);
}

BOOST_AUTO_TEST_SUITE_END()