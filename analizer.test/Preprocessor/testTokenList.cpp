
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenList.h>
#include <Preprocessor/TokenWord.h>
#include "TestFile.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenList)

struct TestToken : public Token {
	const string text;
	TestToken(const string &text) : text(text) {}
	string getText() const { return text; }
	string getLocation() const { return ""; }
	string getTextInString(const string &, const string &) const { return ""; }
	string getFileName() const { return ""; }
	shared_ptr<const Line> getLine() const { return shared_ptr<const Line>(); }
	size_t getBeginPos() const { return 0; }
	size_t getEndPos() const { return 0; }
};

BOOST_AUTO_TEST_CASE(testGetFileName)
{
	TestFile file("test.cpp", {});
	const shared_ptr<const Line> line(new Line(10, "aaaxxxxxaaa", &file));
	const TokenList tokens({shared_ptr<const Token>(new TokenWord(line, 3, 8))});
	BOOST_REQUIRE_EQUAL(tokens.getFileName(), file.getFileName());
}

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
