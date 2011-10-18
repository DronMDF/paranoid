
#include <boost/test/unit_test.hpp>

#include <FileLine.h>
#include <LineUncommented.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteLineUncommented)

BOOST_AUTO_TEST_CASE(testNoModify)
{
	FileLine line(0, "test", 0);
	LineUncommented uncomm(&line);
	BOOST_REQUIRE_EQUAL(uncomm.getText(), line.getText());
	BOOST_REQUIRE_EQUAL(uncomm.getPointer(), &line);
}


BOOST_AUTO_TEST_SUITE_END()
