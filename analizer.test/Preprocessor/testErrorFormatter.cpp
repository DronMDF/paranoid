
#include <boost/test/unit_test.hpp>
#include <Preprocessor/ErrorFormatter.h>
#include <Preprocessor/Error.h>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenWord.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteErrorFormatter)

BOOST_AUTO_TEST_CASE(testTokenFormat)
{
	const File file("test.cpp");
	auto line = make_shared<Line>(1, "123456789", &file);
	auto token = make_shared<TokenWord>(line, 3, 8);
	Error error(token, "numbers error");
	BOOST_REQUIRE_EQUAL(ErrorFormatter(error), 
		"test.cpp:1 error: numbers error\n"
		"123456789\n"
		"   ~~~~~ ");
}

BOOST_AUTO_TEST_SUITE_END()
