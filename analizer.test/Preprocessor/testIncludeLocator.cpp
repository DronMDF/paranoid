
#include <boost/test/unit_test.hpp>
#include <Preprocessor/IncludeLocator.h>
#include <Preprocessor/TokenInclude.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludeLocator)

struct TestToken : public Token {
	string text;
	TestToken(const string &text) : text(text) {}
	string getText() const { return text; }
	string getLocation() const { return ""; }
	string getTextInString(const string &, const string &) const { return ""; }
	string getFileName() const { return ""; }
	shared_ptr<const Line> getLine() const { return shared_ptr<const Line>(); }
	size_t getBeginPos() const { return 0; }
	size_t getEndPos() const { return 0; }
};

struct TestTokenInclude : public TokenInclude {
	TestTokenInclude(const string &arg) : TokenInclude({
		shared_ptr<Token>(new TestToken("#")),
		shared_ptr<Token>(new TestToken("include")),
		shared_ptr<Token>(new TestToken(" ")),
		shared_ptr<Token>(new TestToken(arg))})
	{
	}
	string getFileName() const { return "/test/test.cpp"; }
};

struct TestIncludeLocator : public IncludeLocator {
	const string expected;
	TestIncludeLocator(const vector<const char *> &args, const string &expected) 
		: IncludeLocator(args, {"/usr/include"}), expected(expected) 
	{}
	bool isExists(const string &include) const {
		return include == expected;
	}
};

BOOST_AUTO_TEST_CASE(testNotExists)
{
	const TestIncludeLocator locator({}, "none");
	auto token = shared_ptr<const TokenInclude>(new TestTokenInclude("\"foo.h\""));
	// Not located, no error
	BOOST_REQUIRE(locator.locate(token).empty());
}

BOOST_AUTO_TEST_CASE(testQuotedInCurrentDir)
{
	const TestIncludeLocator locator({}, "/test/foo.h");
	auto token = shared_ptr<const TokenInclude>(new TestTokenInclude("\"foo.h\""));
	BOOST_REQUIRE_EQUAL(locator.locate(token), "/test/foo.h");
}

BOOST_AUTO_TEST_CASE(testQuotedInSelectedDir)
{
	const TestIncludeLocator locator({"-I/manual/include"}, "/manual/include/foo.h");
	auto token = shared_ptr<const TokenInclude>(new TestTokenInclude("\"foo.h\""));
	BOOST_REQUIRE_EQUAL(locator.locate(token), "/manual/include/foo.h");
}

BOOST_AUTO_TEST_CASE(testBracesInSystemDir)
{
	const TestIncludeLocator locator({"-isystem", "/Include"}, "/Include/foo.h");
	auto token = shared_ptr<const TokenInclude>(new TestTokenInclude("<foo.h>"));
	BOOST_REQUIRE_EQUAL(locator.locate(token), "/Include/foo.h");
}

BOOST_AUTO_TEST_CASE(testNoStdInc)
{
	const TestIncludeLocator locator({"-nostdinc"}, "/usr/include/foo.h");
	auto token = shared_ptr<const TokenInclude>(new TestTokenInclude("<foo.h>"));
	// Not located, no error
	BOOST_REQUIRE(locator.locate(token).empty());
}

BOOST_AUTO_TEST_SUITE_END()
