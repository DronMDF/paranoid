
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenPredicate.h>
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenPredicate)

BOOST_AUTO_TEST_CASE(testTextMatch)
{
	TokenPredicate pred("test");
	BOOST_REQUIRE(pred(shared_ptr<Token>(new DummyToken("test"))));
	BOOST_REQUIRE(!pred(shared_ptr<Token>(new DummyToken("text"))));
}

BOOST_AUTO_TEST_SUITE_END()
