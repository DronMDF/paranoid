
#include <list>
#include <memory>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/Line.h>
#include <Preprocessor/Token.h>
#include <Preprocessor/Tokenizer.h>
#include "TestFile.h"
#include "../Assertions.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenizer)

struct fixtureTokenizer {
	const TestFile file;
	list<string> tokens;
	Tokenizer tokenizer;
	
	fixtureTokenizer()
		: file("test_tokenizer.cpp", {}), tokens(),
		  tokenizer([&](const std::shared_ptr<const Token> &t) { tokens.push_back(t->getText()); })
	{
	}
	
	virtual ~fixtureTokenizer();
};

fixtureTokenizer::~fixtureTokenizer() = default;

BOOST_FIXTURE_TEST_CASE(testWord, fixtureTokenizer)
{
	shared_ptr<const Line> line(new Line(1, "word", &file));
	tokenizer.parse(line);
	list<string> expected = { "word", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testTwoWord, fixtureTokenizer)
{
	shared_ptr<const Line> line(new Line(1, "test two", &file));
	tokenizer.parse(line);
	list<string> expected = { "test", " ", "two", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testDoubleQuoting, fixtureTokenizer)
{
	shared_ptr<const Line> line(new Line(1, "test \"quoted \\\" string\"", &file));
	tokenizer.parse(line);
	list<string> expected = { "test", " ", "\"quoted \\\" string\"", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testSingleQuoting, fixtureTokenizer)
{
	shared_ptr<const Line> line(new Line(1, "test 'q'   '\\''", &file));
	tokenizer.parse(line);
	list<string> expected = { "test", " ", "'q'", " ", "'\\''", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testSpecialSymbols, fixtureTokenizer)
{
	shared_ptr<const Line> line(new Line(1, "special<symbols>;", &file));
	tokenizer.parse(line);
	list<string> expected = { "special", "<", "symbols", ">", ";", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testDecimalNumber, fixtureTokenizer)
{
	// Text is not a number, it's another token
	shared_ptr<const Line> line(new Line(1, "222test", &file));
	tokenizer.parse(line);
	list<string> expected = { "222", "test", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testOctalNumbers, fixtureTokenizer)
{
	// 8 and 9 is not a octal number, it's another token (stupid? may be)
	shared_ptr<const Line> line(new Line(1, "034134198", &file));
	tokenizer.parse(line);
	list<string> expected = { "0341341", "98", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testHexNumbers, fixtureTokenizer)
{
	shared_ptr<const Line> line(new Line(1, "0xDEADc0detest", &file));
	tokenizer.parse(line);
	list<string> expected = { "0xDEADc0de", "test", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testComment, fixtureTokenizer)
{
	shared_ptr<const Line> line(new Line(1, "/* 'Specific EOI to master */", &file));
	tokenizer.parse(line);
	list<string> expected = { " ", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testMultilineComment, fixtureTokenizer)
{
	shared_ptr<const Line> line1(new Line(101, "/* \" Page with PAT set to", &file));
	tokenizer.parse(line1);
	shared_ptr<const Line> line2(new Line(102, "*   may consolidate to UC\" */", &file));
	tokenizer.parse(line2);
	list<string> expected = { " ", "\n", " ", "\n"};
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testCppComment, fixtureTokenizer)
{
	shared_ptr<const Line> line1(new Line(101, "token; // Comment", &file));
	tokenizer.parse(line1);
	list<string> expected = { "token", ";", " ", " ", "\n"};
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_FIXTURE_TEST_CASE(testMultilineDoubleQuoteString, fixtureTokenizer)
{
	shared_ptr<const Line> line1(new Line(101, "seq_printf(m, \"%d (%s) %c \\", &file));
	tokenizer.parse(line1);
	shared_ptr<const Line> line2(new Line(102, "%llu %lu %ld\\n\",", &file));
	tokenizer.parse(line2);
	list<string> expected = { "seq_printf", "(", "m", ",", " ", 
		"\"%d (%s) %c \\\n%llu %lu %ld\\n\"", ",", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_SUITE_END()
