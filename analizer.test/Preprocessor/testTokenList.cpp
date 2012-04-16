
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenList.h>
#include <Preprocessor/TokenNewline.h>
#include <Preprocessor/TokenPredicate.h>
#include <Preprocessor/TokenSpace.h>
#include <Preprocessor/TokenWord.h>
#include "../Assertions.h"
#include "../FileStub.h"
#include "../TokenStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenList)

void CUSTOM_EQUAL_TOKENLIST_TOKENS_TEXT(const TokenList &token_list, const list<string> &expected)
{
	list<string> actual;
	token_list.forEachToken([&actual](const shared_ptr<const Token> &t){ 
		actual.push_back(t->getText());
	});
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(actual, expected);
}

BOOST_AUTO_TEST_CASE(testGetFileName)
{
	const FileStub file("test.cpp", {});
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
	auto token = make_shared<TokenStub>("test");
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

BOOST_AUTO_TEST_CASE(ShouldReplaceTokens)
{
	// Given
	TokenList token_list({
		make_shared<TokenStub>("#define"),
		make_shared<TokenSpace>(shared_ptr<Line>(), 0, 0),
		make_shared<TokenStub>("a"),
		make_shared<TokenSpace>(shared_ptr<Line>(), 0, 0),
		make_shared<TokenStub>("0"),
		make_shared<TokenNewline>(shared_ptr<Line>())
	});
	// When
	token_list.replaceToken({"#define", isSpace, Some(Not(isEol))},
		[](const list<shared_ptr<Token>> &l){ return make_shared<TokenList>(l); });
	// Then
	CUSTOM_EQUAL_TOKENLIST_TOKENS_TEXT(token_list, { "#define a 0", "\n" });
}

BOOST_AUTO_TEST_CASE(ShouldReplaceTokenInBracket)
{
	// Given
	TokenList token_list({
		make_shared<TokenStub>("#include"),
		make_shared<TokenSpace>(shared_ptr<Line>(), 0, 0),
		make_shared<TokenStub>("<"),
		make_shared<TokenStub>("stdio"),
		make_shared<TokenStub>("."),
		make_shared<TokenStub>("h"),
		make_shared<TokenStub>(">"),
		make_shared<TokenNewline>(shared_ptr<Line>())
	});
	// When
	token_list.replaceToken({"#include", Optional(Some(isSpace)), "<", Some(Not(">")), ">"},
		[](const list<shared_ptr<Token>> &l){ return make_shared<TokenList>(l); });
	// Then
	CUSTOM_EQUAL_TOKENLIST_TOKENS_TEXT(token_list, { "#include <stdio.h>", "\n" });
}

BOOST_AUTO_TEST_CASE(ShouldReplaceTokensRecursively)
{
	// Given
	list<shared_ptr<Token>> tokens = {
		make_shared<TokenStub>("a"),
		make_shared<TokenStub>("b"),
		make_shared<TokenStub>("c")
	};
	TokenList token_list({
		make_shared<TokenList>(tokens)
	});
	// When
	token_list.replaceToken({"b"}, 
		[](const list<shared_ptr<Token>> &){ return make_shared<TokenStub>("x"); });
	// Then
	CUSTOM_EQUAL_TOKENLIST_TOKENS_TEXT(token_list, { "axc" });
}

BOOST_AUTO_TEST_CASE(ShouldReplaceAllDepth)
{
	// Given
	TokenList token_list({
		make_shared<TokenStub>("{"),
		make_shared<TokenStub>("{"),
		make_shared<TokenStub>("b"),
		make_shared<TokenStub>("}"),
		make_shared<TokenStub>("}")
	});
	// When
	token_list.replaceToken({"{", Optional(Some(Not("{"))), "}"}, [](const list<shared_ptr<Token>> &l) {
		// Decorated list...
		list<shared_ptr<Token>> il(l);
		il.push_front(make_shared<TokenStub>("("));
		il.push_back(make_shared<TokenStub>(")"));
		return make_shared<TokenList>(il); 
	});
	// Then
	BOOST_REQUIRE_EQUAL(token_list.getText(), "({({b})})");
}

BOOST_AUTO_TEST_SUITE_END()
