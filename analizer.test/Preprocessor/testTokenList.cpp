
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenList.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenList)

struct TestToken : public Token {
	const string text;
	TestToken(const string &text) : text(text) {}
	string getText() const { return text; }
	string getLocation() const { return string(); }
	string getTextInString(const string &, const string &) const
		{ return string(); }
};

BOOST_AUTO_TEST_CASE(testEmptyList)
{
	const list<shared_ptr<const Token>> tokens;
	const TokenList token_list(tokens);
	BOOST_REQUIRE_EQUAL(token_list.getText(), string());
}

BOOST_AUTO_TEST_CASE(testOneInList)
{
	const list<shared_ptr<const Token>> tokens(1, shared_ptr<const Token>(new TestToken("test")));
	const TokenList token_list(tokens);
	BOOST_REQUIRE_EQUAL(token_list.getText(), tokens.front()->getText());
}

BOOST_AUTO_TEST_SUITE_END()
