
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

BOOST_AUTO_TEST_SUITE_END()
