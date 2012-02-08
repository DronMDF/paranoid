
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenWord.h>
#include "TestFile.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenWord)

BOOST_AUTO_TEST_CASE(testGetTextFromLine)
{
	auto line = make_shared<Line>(10, "aaaxxxxxaaa", static_cast<File *>(0));
	const TokenWord token(line, 3, 8);
	BOOST_REQUIRE_EQUAL(token.getText(), "xxxxx");
}

BOOST_AUTO_TEST_CASE(testGetFileName)
{
	const TestFile file("test.cpp", {});
	auto line = make_shared<Line>(10, "aaaxxxxxaaa", &file);
	const TokenWord token(line, 3, 8);
	BOOST_REQUIRE_EQUAL(token.getFileName(), file.getFileName());
}

BOOST_AUTO_TEST_SUITE_END()
