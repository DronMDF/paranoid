
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenList.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenList)

BOOST_AUTO_TEST_CASE(testEmptyList)
{
	const list<shared_ptr<const Token>> tokens;
	const TokenList token_list(tokens);
	BOOST_REQUIRE_EQUAL(token_list.getText(), string());
}

BOOST_AUTO_TEST_SUITE_END()
