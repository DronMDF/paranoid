
#include <boost/test/unit_test.hpp>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/File.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteTokenInclude)

BOOST_AUTO_TEST_CASE(testConstruct)
{
	const list<shared_ptr<const Token>> tokens;
	TokenInclude ti(tokens);
	ti.include(shared_ptr<File>(new File("test.h")));
}

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

BOOST_AUTO_TEST_CASE(testSystemInclude)
{
	const auto token = shared_ptr<Token>(new TestToken("<test.h>"));
	const list<shared_ptr<const Token>> tokens = { token };
	TokenInclude ti(tokens);
	ti.include(shared_ptr<File>());
	BOOST_REQUIRE(ti.isSystem());
	BOOST_REQUIRE_EQUAL(ti.getHeaderName(), "test.h");
}

BOOST_AUTO_TEST_CASE(testLocalInclude)
{
	const auto token = shared_ptr<Token>(new TestToken("\"local.h\""));
	const list<shared_ptr<const Token>> tokens = { token };
	TokenInclude ti(tokens);
	ti.include(shared_ptr<File>());
	BOOST_REQUIRE(!ti.isSystem());
	BOOST_REQUIRE_EQUAL(ti.getHeaderName(), "local.h");
}

BOOST_AUTO_TEST_SUITE_END()
