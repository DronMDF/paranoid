
#include <list>
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Tokenizer.h>
#include <Preprocessor/Token.h>
#include <Preprocessor/FileLine.h>
#include "TestFile.h"
#include "../Assertions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenizer)

struct fixtureTokenizer {
	const TestFile file;
	list<string> tokens;
	Tokenizer tokenizer;
	
	fixtureTokenizer()
		: file("test_tokenizer.cpp"), tokens(),
		  tokenizer([&](const std::shared_ptr<const Token> &t) { tokens.push_back(t->getText()); })
	{
	}
	
	virtual ~fixtureTokenizer();
};

fixtureTokenizer::~fixtureTokenizer() = default;

BOOST_FIXTURE_TEST_CASE(testWord, fixtureTokenizer)
{
	shared_ptr<const Line> line(new FileLine(1, "word", &file));
	tokenizer.parse(line);
	list<string> expected = { "word", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testTwoWord, fixtureTokenizer)
{
	shared_ptr<const Line> line(new FileLine(1, "test two", &file));
	tokenizer.parse(line);
	list<string> expected = { "test", " ", "two", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testDoubleQuoting, fixtureTokenizer)
{
	shared_ptr<const Line> line(new FileLine(1, "test \"quoted \\\" string\"", &file));
	tokenizer.parse(line);
	list<string> expected = { "test", " ", "\"quoted \\\" string\"", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testSingleQuoting, fixtureTokenizer)
{
	shared_ptr<const Line> line(new FileLine(1, "test 'q'   '\\''", &file));
	tokenizer.parse(line);
	list<string> expected = { "test", " ", "'q'", " ", "'\\''", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_SUITE_END()
