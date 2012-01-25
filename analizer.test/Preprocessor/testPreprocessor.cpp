
#include <boost/test/unit_test.hpp>
#include <boost/foreach.hpp>
#include <boost/range/algorithm/find.hpp>
#include <Preprocessor/Error.h>
#include <Preprocessor/File.h>
#include <Preprocessor/Line.h>
#include <Preprocessor/Token.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/Preprocessor.h>
#include "TestFile.h"
#include "../Assertions.h"

using namespace std;
using boost::find;

BOOST_AUTO_TEST_SUITE(suitePreprocessor)

struct TestPreprocessor : public Preprocessor {
	TestPreprocessor() : 
		Preprocessor([](const std::shared_ptr<const TokenInclude> &token){ 
				return token->getHeaderName(); 
			},
			"test.cpp")
	{}
	
	using Preprocessor::files;
};

BOOST_AUTO_TEST_CASE(testConstruct)
{
	TestPreprocessor pp;
	BOOST_REQUIRE_EQUAL(pp.files.front().second->getLocation(), "test.cpp");
}

BOOST_AUTO_TEST_CASE(testTokenize)
{
	TestPreprocessor pp;
	auto file = shared_ptr<File>(new TestFile("test.cpp", 
		{ "int main(int argc, char **argv) {", " return 0;", " }" }));
	pp.files.clear();
	pp.files.push_back(make_pair("test.cpp", file));
	
	// Parse
	pp.tokenize();
	
	list<string> tokens;
	pp.getTokens("test.cpp", [&tokens](const shared_ptr<const Token> &t){ tokens.push_back(t->getText()); });
	
	list<string> expected = { "int", " ", "main", "(", "int", " ", "argc", ",", " ", 
		"char", " ", "*", "*", "argv", ")", " ", "{", "\n", 
		" ", "return", " ", "0", ";", "\n", " ", "}", "\n" };
	CUSTOM_REQUIRE_EQUAL_COLLECTIONS(tokens, expected);
}

BOOST_AUTO_TEST_CASE(testInclude)
{
	TestPreprocessor pp;
	auto included = shared_ptr<File>(new TestFile("included.h", {}));
	auto includer = shared_ptr<File>(new TestFile("includer.cpp", {"#include \"included.h\""}));
	
	pp.files.clear();
	pp.files.push_back(make_pair("included.h", included));
	pp.files.push_back(make_pair("includer.cpp", includer));

	pp.tokenize();
	
	// included should be marked as 'included' from includer.cpp
	BOOST_REQUIRE_EQUAL(included->getLocation(), "includer.cpp:1\nincluded.h");
}

BOOST_AUTO_TEST_CASE(testLocate)
{
	struct tpp : public Preprocessor {
		tpp() : Preprocessor(
			[](const std::shared_ptr<const TokenInclude> &token) -> string { 
				throw Error(token, "test");
			}, 
			"nothing")
		{}
		using Preprocessor::files;
	} pp;

	auto file = shared_ptr<File>(new TestFile("throw.cpp", {"#include \"included.h\""}));
	
	pp.files.clear();
	pp.files.push_back(make_pair("throw.cpp", file));

	BOOST_REQUIRE_THROW(pp.tokenize(), Error);
}

BOOST_AUTO_TEST_CASE(testForEach)
{
	TestPreprocessor pp;
	pp.files.clear();
	pp.files.push_back(make_pair("f1.cpp", shared_ptr<File>(new TestFile("f1.cpp", {}))));
	pp.files.push_back(make_pair("f2.cpp", shared_ptr<File>(new TestFile("f2.cpp", {}))));

	list<string> names;
	pp.forEachFile([&names](const shared_ptr<File> &f){ names.push_back(f->getFileName()); });
	BOOST_REQUIRE_EQUAL(names.size(), 2);
	BOOST_REQUIRE(find(names, "f1.cpp") != names.end());
	BOOST_REQUIRE(find(names, "f2.cpp") != names.end());
}

BOOST_AUTO_TEST_SUITE_END()

