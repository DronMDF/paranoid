
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <File.h>
#include <Token.h>
#include <Error.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteError)

BOOST_AUTO_TEST_CASE(testErrorFromToken)
{
	istringstream in("123456789");
	const File file(in);
	const Token token(file.begin()->get(), 3, 5);
	Error error(token, "numbers error");
	BOOST_REQUIRE_EQUAL(error.what(), "<unknown>:1 error: numbers error\n123456789");
}

BOOST_AUTO_TEST_SUITE_END()
