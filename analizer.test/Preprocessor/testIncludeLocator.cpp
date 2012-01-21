
#include <boost/test/unit_test.hpp>
#include <Preprocessor/IncludeLocator.h>
#include <Preprocessor/TokenInclude.h>
#include "DummyToken.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteIncludeLocator)

struct TestTokenInclude : public TokenInclude {
	TestTokenInclude(const string &arg) : TokenInclude({
		shared_ptr<Token>(new DummyToken("#")),
		shared_ptr<Token>(new DummyToken("include")),
		shared_ptr<Token>(new DummyToken(" ")),
		shared_ptr<Token>(new DummyToken(arg))})
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
