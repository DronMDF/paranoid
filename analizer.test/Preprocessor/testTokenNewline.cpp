
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenNewline.h>
#include "TestFile.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenNewline)

BOOST_AUTO_TEST_CASE(testGetText)
{
	auto line = make_shared<Line>(10, "aaaxxxxxaaa", static_cast<File *>(0));
	const TokenNewline token(line);
	BOOST_REQUIRE_EQUAL(token.getText(), "\n");
}

BOOST_AUTO_TEST_CASE(testGetFileName)
{
	TestFile file("test.cpp", {});
	auto line = make_shared<Line>(10, "aaaxxxxxaaa", &file);
	const TokenNewline token(line);
	BOOST_REQUIRE_EQUAL(token.getFileName(), file.getFileName());
}

BOOST_AUTO_TEST_SUITE_END()
