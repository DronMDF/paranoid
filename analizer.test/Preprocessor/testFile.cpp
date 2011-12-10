
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <boost/test/unit_test.hpp>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/Token.h>
#include <Preprocessor/TokenInclude.h>
#include "../Assertions.h"

using namespace std;
using boost::lexical_cast;
using boost::transform;

BOOST_AUTO_TEST_SUITE(suiteFile)

struct TestFile : public File {
	const list<string> lines;
	TestFile(const list<string> &lines) : File("testFile.cpp"), lines(lines) {}
	void forEachLine(function<void (const shared_ptr<const Line> &)> lineparser) const {
		unsigned n = 0;
		BOOST_FOREACH(const auto &l, lines) {
			shared_ptr<const Line> line(new Line(++n, l, this));
			lineparser(line);
		}
	}
};

void include(const shared_ptr<TokenInclude> &, const string &, bool) 
{
}

BOOST_AUTO_TEST_CASE(testGetConstructedLocation)
{
	const File file("test.cpp");
	BOOST_REQUIRE_EQUAL(file.getLocation(), "test.cpp");
}

BOOST_AUTO_TEST_CASE(testTokenize)
{
	TestFile file({"012345"});
	file.tokenize(include);
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "012345", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testTokenize2)
{
	TestFile file({"aaa bbb"});
	file.tokenize(include);
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "aaa", " ", "bbb", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testEscapedNewline)
{
	TestFile file({"#define a \\", "(foo)"});
	file.tokenize(include);
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "#", "define", " ", "a", " ", "(", "foo", ")", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testIncludeSystem)
{
	TestFile file({"#include <test.h>"});

	shared_ptr<const TokenInclude> tf;
	string filename;
	bool system = false;
	
	file.tokenize([&](const shared_ptr<TokenInclude> &ti, const string &n, bool s) {
		tf = ti;
		filename = n;
		system = s;
	});

	BOOST_REQUIRE_EQUAL(tf->getText(), "#include <test.h>");
	BOOST_REQUIRE_EQUAL(tf->getLocation(), "testFile.cpp:1");
	BOOST_REQUIRE_EQUAL(filename, "test.h");
	BOOST_REQUIRE(system);
	
	list<string> tokens;
	file.getTokens([&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "#include <test.h>", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testIncludeLocal)
{
	TestFile file({"#include \"test.h\""});

	shared_ptr<const TokenInclude> tf;
	string filename;
	bool system = false;
	
	file.tokenize([&](const shared_ptr<TokenInclude> &ti, const string &n, bool s) {
		tf = ti;
		filename = n;
		system = s;
	});

	BOOST_REQUIRE_EQUAL(tf->getText(), "#include \"test.h\"");
	BOOST_REQUIRE_EQUAL(tf->getLocation(), "testFile.cpp:1");
	BOOST_REQUIRE_EQUAL(filename, "test.h");
	BOOST_REQUIRE(!system);
	
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
	
	TestFile file({});
	file.includedFrom(shared_ptr<TokenInclude>(new TestToken()));
	BOOST_REQUIRE_EQUAL(file.getLocation(), "Parent.cpp:5\ntestFile.cpp");
}

BOOST_AUTO_TEST_SUITE_END()
