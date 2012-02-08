
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Error.h>
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteError)

BOOST_AUTO_TEST_CASE(testErrorFromToken)
{
	auto token = make_shared<DummyToken>("test");
	const Error error(token, "numbers error");
	BOOST_REQUIRE_EQUAL(error.token, token);
	BOOST_REQUIRE_EQUAL(error.message, "numbers error");
}

BOOST_AUTO_TEST_SUITE_END()
