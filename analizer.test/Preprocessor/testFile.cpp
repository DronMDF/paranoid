
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <File.h>
#include <Line.h>
#include "../Assertions.h"

using namespace std;
using boost::lexical_cast;
using boost::transform;

BOOST_AUTO_TEST_SUITE(suiteFile)

BOOST_AUTO_TEST_CASE(testGetConstructedLocation)
{
	const File file(0, "test.cpp");
	BOOST_REQUIRE_EQUAL(file.getLocation(), "test.cpp");
}

BOOST_AUTO_TEST_CASE(Construction1)
{
	istringstream in("line1\nline2\nline3\n");
	const File file(in);
	
	list<string> lines;
	transform(file, back_inserter(lines), 
		  [](const shared_ptr<const Line> &l){ return l->getText(); });

	list<string> expected = { "line1", "line2", "line3" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(lines, expected);
}

BOOST_AUTO_TEST_CASE(Foreach)
{
	istringstream in("line1\nline2\nline3\n");
	const File file(in);
	unsigned number = 1;
	// for(const Line &line : file) {	// range-based for появится в gcc-4.6
	BOOST_FOREACH(const auto &line, file) {
		if (number < 4) {
			BOOST_REQUIRE_EQUAL(line->getText(), "line" + lexical_cast<string>(number));
		} else {
			BOOST_REQUIRE(line->getText().empty());
		}
		number++;
	}
}

BOOST_AUTO_TEST_CASE(testGetLocation)
{
	istringstream in; 
	const File file(in);
	BOOST_REQUIRE_EQUAL(file.getLocation(), "<unknown>");
}

BOOST_AUTO_TEST_SUITE_END()
