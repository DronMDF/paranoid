
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <File.h>
#include <Token.h>
#include <Error.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteError)

const string SSEL = "\033[1;31m";
const string ESEL = "\033[0m";

BOOST_AUTO_TEST_CASE(testErrorFromToken)
{
	istringstream in("123456789");
	const File file(in);
	const Token token(*(file.begin()), 3, 5);
	Error error(token, "numbers error");
	BOOST_REQUIRE_EQUAL(error.what(), "<unknown>:1 error: numbers error\n"
		"123" + SSEL + "45678" + ESEL + "9");
}

BOOST_AUTO_TEST_CASE(testErrorFromLine)
{
	istringstream in("123456789");
	const File file(in);
	Error error(**(file.begin()), 5, string::npos, "wrong quote");
	BOOST_REQUIRE_EQUAL(error.what(), "<unknown>:1 error: wrong quote\n"
		"12345" + SSEL + "6789" + ESEL);
}

BOOST_AUTO_TEST_SUITE_END()
