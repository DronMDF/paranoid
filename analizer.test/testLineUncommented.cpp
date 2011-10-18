
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

BOOST_AUTO_TEST_CASE(testOneHole)
{
	FileLine line(0, "0123456789", 0);
	LineUncommented uncomm(&line);
	uncomm.hole(3, 7);
	BOOST_REQUIRE_EQUAL(uncomm.getText(), "012     89");
	BOOST_REQUIRE_EQUAL(uncomm.getPointer(), &line);
}

BOOST_AUTO_TEST_SUITE_END()
