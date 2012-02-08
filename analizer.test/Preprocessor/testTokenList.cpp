
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
	auto line = make_shared<Line>(10, "aaaxxxxxaaa", &file);
	const TokenList tokens({make_shared<TokenWord>(line, 3, 8)});
	BOOST_REQUIRE_EQUAL(tokens.getFileName(), file.getFileName());
}

BOOST_AUTO_TEST_CASE(testEmptyList)
{
	const TokenList token_list({});
	BOOST_REQUIRE_EQUAL(token_list.getText(), "");
}

BOOST_AUTO_TEST_CASE(testOneInList)
{
	auto token = make_shared<DummyToken>("test");
	const TokenList token_list({token});
	BOOST_REQUIRE_EQUAL(token_list.getText(), token->getText());
}

BOOST_AUTO_TEST_CASE(testTwoInList)
{
	auto line = make_shared<Line>(10, "aaaxxxxxaaa", static_cast<File *>(0));
	const TokenList token_list({
		make_shared<TokenWord>(line, 3, 5),
		make_shared<TokenWord>(line, 5, 7),
		make_shared<TokenWord>(line, 7, 8)
	});
	BOOST_REQUIRE_EQUAL(token_list.getBeginPos(), 3);
	BOOST_REQUIRE_EQUAL(token_list.getEndPos(), 8);
}

BOOST_AUTO_TEST_SUITE_END()
