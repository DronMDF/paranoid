
#include<memory>	// <- Check for optional
#include <boost/test/unit_test.hpp>
#include <Analizer/Analizer.h>
#include <Preprocessor/Error.h>
#include <Preprocessor/TokenInclude.h>
#include <Preprocessor/TokenPredicate.h>
#include "../FileStub.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(suiteAnalizer)

BOOST_AUTO_TEST_CASE(testUnusedInclude)
{
	list<string> flines = { "#include <test.h>", "// none" };
	auto file = make_shared<FileStub>("none", flines);
	file->tokenize();
	file->replaceToken({"#include", Optional(Some(isSpace)), "<", Some(Not(">")), ">"},
		[](const list<shared_ptr<const Token>> &t){ return make_shared<TokenInclude>(t); });
	
	Analizer analizer;
	analizer.checkFile(file);
	
	BOOST_REQUIRE_EQUAL(analizer.getResult().size(), 1);
	BOOST_REQUIRE_EQUAL(analizer.getResult().front().message, "Unused include");
}

BOOST_AUTO_TEST_SUITE_END()
