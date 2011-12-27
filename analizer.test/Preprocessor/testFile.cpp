
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/Token.h>
#include <Preprocessor/TokenInclude.h>
#include "TestFile.h"
#include "../Assertions.h"

using namespace std;
using boost::lexical_cast;
using boost::transform;

BOOST_AUTO_TEST_SUITE(suiteFile)

void include(const shared_ptr<TokenInclude> &)
{
}

BOOST_AUTO_TEST_CASE(testGetConstructedLocation)
{
	const File file("test.cpp");
	BOOST_REQUIRE_EQUAL(file.getLocation(), "test.cpp");
}

BOOST_AUTO_TEST_CASE(testTokenize)
{
	TestFile file("testFile.cpp", {"012345"});
	file.tokenize(include);
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "012345", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testTokenize2)
{
	TestFile file("testFile.cpp", {"aaa bbb"});
	file.tokenize(include);
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "aaa", " ", "bbb", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testEscapedNewline)
{
	TestFile file("testFile.cpp", {"#define a \\", "(foo)"});
	file.tokenize(include);
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "#", "define", " ", "a", " ", "(", "foo", ")", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testIncludeSystem)
{
	TestFile file("testFile.cpp", {"#include <test.h>"});

	shared_ptr<const TokenInclude> ti;
	file.tokenize([&](const shared_ptr<TokenInclude> &t) { ti = t; });

	BOOST_REQUIRE_EQUAL(ti->getText(), "#include <test.h>");
	BOOST_REQUIRE_EQUAL(ti->getLocation(), "testFile.cpp:1");
	BOOST_REQUIRE_EQUAL(ti->getHeaderName(), "test.h");
	BOOST_REQUIRE(ti->isSystem());
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "#include <test.h>", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testIncludeLocal)
{
	TestFile file("testFile.cpp", {"#include \"test.h\""});

	shared_ptr<const TokenInclude> ti;
	file.tokenize([&](const shared_ptr<TokenInclude> &t) { ti = t; });

	BOOST_REQUIRE_EQUAL(ti->getText(), "#include \"test.h\"");
	BOOST_REQUIRE_EQUAL(ti->getLocation(), "testFile.cpp:1");
	BOOST_REQUIRE_EQUAL(ti->getHeaderName(), "test.h");
	BOOST_REQUIRE(!ti->isSystem());
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "#include \"test.h\"", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testIncludeFrom)
{
	struct TestToken : public TokenInclude {
		TestToken() : TokenInclude({}) {}
		string getLocation() const { return "Parent.cpp:5"; }
	};
	
	TestFile file("testFile.cpp", {});
	file.includedFrom(shared_ptr<TokenInclude>(new TestToken()));
	BOOST_REQUIRE_EQUAL(file.getLocation(), "Parent.cpp:5\ntestFile.cpp");
}

BOOST_AUTO_TEST_SUITE_END()
