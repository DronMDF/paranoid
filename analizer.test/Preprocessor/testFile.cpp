
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/Token.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenPredicate.h>
#include "../Assertions.h"
#include "../FileStub.h"

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

BOOST_AUTO_TEST_CASE(testGetFileName)
{
	const File file("test.cpp");
	BOOST_REQUIRE_EQUAL(file.getFileName(), "test.cpp");
}

BOOST_AUTO_TEST_CASE(testTokenize)
{
	FileStub file("testFile.cpp", {"012345"});
	file.tokenize();
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "012345", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testTokenize2)
{
	FileStub file("testFile.cpp", {"aaa bbb"});
	file.tokenize();
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "aaa", " ", "bbb", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testEscapedNewline)
{
	FileStub file("testFile.cpp", {"#define a \\", "(foo)"});
	file.tokenize();
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "#define", " ", "a", " ", "(", "foo", ")", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

// BOOST_AUTO_TEST_CASE(testIncludeSystem)
// {
// 	FileStub file("testFile.cpp", {"#include <test.h>"});
// 
// 	shared_ptr<const TokenInclude> ti;
// 	file.tokenize();
// 
// 	BOOST_REQUIRE_EQUAL(ti->getText(), "#include <test.h>");
// 	BOOST_REQUIRE_EQUAL(ti->getLocation(), "testFile.cpp:1");
// 	BOOST_REQUIRE_EQUAL(ti->getHeaderName(), "test.h");
// 	BOOST_REQUIRE(ti->isSystem());
// 	
// 	list<string> tokens;
// 	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
// 	
// 	list<string> expected = { "#include <test.h>", "\n" };
// 	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
// }

// BOOST_AUTO_TEST_CASE(testIncludeLocal)
// {
// 	FileStub file("testFile.cpp", {"#include \"test.h\""});
// 
// 	shared_ptr<const TokenInclude> ti;
// 	file.tokenize();
// 
// 	BOOST_REQUIRE_EQUAL(ti->getText(), "#include \"test.h\"");
// 	BOOST_REQUIRE_EQUAL(ti->getLocation(), "testFile.cpp:1");
// 	BOOST_REQUIRE_EQUAL(ti->getHeaderName(), "test.h");
// 	BOOST_REQUIRE(!ti->isSystem());
// 	
// 	list<string> tokens;
// 	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
// 	
// 	list<string> expected = { "#include \"test.h\"", "\n" };
// 	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
// }

BOOST_AUTO_TEST_CASE(testIncludeFrom)
{
	struct TestToken : public TokenInclude {
		TestToken() : TokenInclude({}) {}
		string getLocation() const { return "Parent.cpp:5"; }
	};
	
	FileStub file("testFile.cpp", {});
	file.includedFrom(make_shared<TestToken>());
	BOOST_REQUIRE_EQUAL(file.getLocation(), "Parent.cpp:5\ntestFile.cpp");
}

BOOST_AUTO_TEST_CASE(testFileTokenReplace)
{
	FileStub file("none", {"#define a 0"});
	file.tokenize();
	file.replaceToken({"#define", isSpace, Some(Not(isEol))},
		[](const list<shared_ptr<const Token>> &l){ return make_shared<TokenList>(l); });

	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "#define a 0", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_SUITE_END()
