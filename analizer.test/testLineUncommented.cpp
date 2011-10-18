
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
	uncomm.hide(3, 7);
	BOOST_REQUIRE_EQUAL(uncomm.getText(), "012    789");
}

BOOST_AUTO_TEST_CASE(testTwoHole)
{
	FileLine line(0, "0123456789", 0);
	LineUncommented uncomm(&line);
	uncomm.hide(2, 5);
	uncomm.hide(6, 8);
	BOOST_REQUIRE_EQUAL(uncomm.getText(), "01   5  89");
}

BOOST_AUTO_TEST_CASE(testOpen)
{
	FileLine line(0, "0123456789", 0);
	LineUncommented uncomm(&line);
	uncomm.hide(5, string::npos);
	BOOST_REQUIRE_EQUAL(uncomm.getText(), "01234     ");
}

BOOST_AUTO_TEST_SUITE_END()
