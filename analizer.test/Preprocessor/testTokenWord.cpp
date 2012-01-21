
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenWord.h>
#include "TestFile.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenWord)

BOOST_AUTO_TEST_CASE(testGetTextFromLine)
{
	const shared_ptr<const Line> line(new Line(10, "aaaxxxxxaaa", 0));
	const TokenWord token(line, 3, 8);
	BOOST_REQUIRE_EQUAL(token.getText(), "xxxxx");
}

BOOST_AUTO_TEST_CASE(testGetFileName)
{
	const TestFile file("test.cpp", {});
	const shared_ptr<const Line> line(new Line(10, "aaaxxxxxaaa", &file));
	const TokenWord token(line, 3, 8);
	BOOST_REQUIRE_EQUAL(token.getFileName(), file.getFileName());
}

BOOST_AUTO_TEST_SUITE_END()
