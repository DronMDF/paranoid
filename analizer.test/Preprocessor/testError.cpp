
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Error.h>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/TokenWord.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteError)

BOOST_AUTO_TEST_CASE(testErrorFromToken)
{
	const File file("test.cpp");
	const shared_ptr<Line> line(new Line(1, "123456789", &file));
	const shared_ptr<Token> token(new TokenWord(line, 3, 8));
	Error error(token, "numbers error");
	BOOST_REQUIRE_EQUAL(error.what(), "test.cpp:1 error: numbers error\n123456789");
}

BOOST_AUTO_TEST_SUITE_END()
