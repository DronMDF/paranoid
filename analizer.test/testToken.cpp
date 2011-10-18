
#include <boost/test/unit_test.hpp>
#include <FileLine.h>
#include <Token.h>

BOOST_AUTO_TEST_SUITE(suiteToken)

BOOST_AUTO_TEST_CASE(GetTextFromLine)
{
	const FileLine line(10, "aaaxxxxxaaa", 0);
	const Token token(&line, 3, 5);
	BOOST_REQUIRE_EQUAL(token.getText(), "xxxxx");
}

BOOST_AUTO_TEST_CASE(GetEmptyText)
{
	// Специальный случай Токена - пробельный токен
	const Token token;
	BOOST_REQUIRE_EQUAL(token.getText(), " ");
}

BOOST_AUTO_TEST_SUITE_END()
