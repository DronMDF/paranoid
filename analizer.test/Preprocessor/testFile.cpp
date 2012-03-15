
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <Analizer/ExpressionDefine.h>
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
	
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(file.getTokensText(), { "012345", "\n" });
}

BOOST_AUTO_TEST_CASE(testTokenize2)
{
	FileStub file("testFile.cpp", {"aaa bbb"});
	file.tokenize();
	
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(file.getTokensText(), { "aaa", " ", "bbb", "\n" });
}

BOOST_AUTO_TEST_CASE(testEscapedNewline)
{
	FileStub file("testFile.cpp", {"#define a \\", "(foo)"});
	file.tokenize();
	
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(file.getTokensText(), 
		{ "#define", " ", "a", " ", "(", "foo", ")", "\n" });
}

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

	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(file.getTokensText(), { "#define a 0", "\n" });
}

BOOST_AUTO_TEST_CASE(testFileTokenReplace2)
{
	FileStub file("none", {"#include <stdio.h>"});
	file.tokenize();
	file.replaceToken({"#include", Optional(Some(isSpace)), "<", Some(Not(">")), ">"},
		[](const list<shared_ptr<const Token>> &l){ return make_shared<TokenInclude>(l); });

	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(file.getTokensText(), { "#include <stdio.h>", "\n" });
}

BOOST_AUTO_TEST_CASE(testFileExportedName)
{
	FileStub file("none", {"#define a 0"});
	file.tokenize();
	file.replaceToken({"#define", isSpace, Some(Not(isEol))},
		[](const list<shared_ptr<const Token>> &l){ return make_shared<ExpressionDefine>(l); });

	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(file.getExportedText(), {"a"});
}

BOOST_AUTO_TEST_SUITE_END()
