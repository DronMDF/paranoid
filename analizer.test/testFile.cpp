
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>
#include <File.h>

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(suiteFile)

BOOST_AUTO_TEST_CASE(Construction1)
{
	istringstream in("line1\nline2\nline3\n");
	const File file(in);
	
	File::const_iterator it = file.begin();
	BOOST_REQUIRE_EQUAL(it->getNumber(), 1U);
	BOOST_REQUIRE_EQUAL(it->getText(), "line1");
	++it;
	BOOST_REQUIRE_EQUAL(it->getNumber(), 2U);
	BOOST_REQUIRE_EQUAL(it->getText(), "line2");
	++it;
	BOOST_REQUIRE_EQUAL(it->getNumber(), 3U);
	BOOST_REQUIRE_EQUAL(it->getText(), "line3");
	++it;
	BOOST_REQUIRE_EQUAL(it->getNumber(), 4U);
	BOOST_REQUIRE(it->getText().empty());
	++it;
	BOOST_REQUIRE(it == file.end());
}

BOOST_AUTO_TEST_CASE(Foreach)
{
	istringstream in("line1\nline2\nline3\n");
	const File file(in);
	unsigned number = 1;
	BOOST_FOREACH(const Line &line, file) {
		BOOST_REQUIRE_EQUAL(line.getNumber(), number);
		if (number < 4) {
			BOOST_REQUIRE_EQUAL(line.getText(), "line" + lexical_cast<string>(number));
		} else {
			BOOST_REQUIRE(line.getText().empty());
		}
		number++;
	}
}

BOOST_AUTO_TEST_SUITE_END()
