
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenList.h>
#include <Preprocessor/TokenWord.h>
#include "TestFile.h"
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenList)

BOOST_AUTO_TEST_CASE(testGetFileName)
{
	const TestFile file("test.cpp", {});
	const shared_ptr<const Line> line(new Line(10, "aaaxxxxxaaa", &file));
	const TokenList tokens({shared_ptr<const Token>(new TokenWord(line, 3, 8))});
	BOOST_REQUIRE_EQUAL(tokens.getFileName(), file.getFileName());
}

BOOST_AUTO_TEST_CASE(testEmptyList)
{
	const TokenList token_list({});
	BOOST_REQUIRE_EQUAL(token_list.getText(), "");
}

BOOST_AUTO_TEST_CASE(testOneInList)
{
	const shared_ptr<const Token> token(new DummyToken("test"));
	const TokenList token_list({token});
	BOOST_REQUIRE_EQUAL(token_list.getText(), token->getText());
}

BOOST_AUTO_TEST_CASE(testTwoInList)
{
	const shared_ptr<const Line> line(new Line(10, "aaaxxxxxaaa", 0));
	const TokenList token_list({
		shared_ptr<const Token>(new TokenWord(line, 3, 5)),
		shared_ptr<const Token>(new TokenWord(line, 5, 7)),
		shared_ptr<const Token>(new TokenWord(line, 7, 8))
	});
	BOOST_REQUIRE_EQUAL(token_list.getBeginPos(), 3);
	BOOST_REQUIRE_EQUAL(token_list.getEndPos(), 8);
}

BOOST_AUTO_TEST_SUITE_END()
